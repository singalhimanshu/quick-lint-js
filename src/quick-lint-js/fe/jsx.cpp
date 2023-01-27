// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#include <algorithm>
#include <quick-lint-js/assert.h>
#include <quick-lint-js/container/c-string-list.h>
#include <quick-lint-js/container/linked-bump-allocator.h>
#include <quick-lint-js/fe/jsx.h>
#include <quick-lint-js/port/char8.h>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std::literals::string_view_literals;

namespace quick_lint_js {
const hash_map<string8_view, jsx_attribute>& jsx_attribute_aliases() {
  static linked_bump_allocator<1> string_allocator("jsx_attribute_aliases");
  static const hash_map<string8_view, jsx_attribute> cache = [] {
    // FIXME(strager): This is very inefficient.
    hash_map<string8_view, jsx_attribute> aliases{
        {u8"class"_sv, {u8"className"_sv}},
    };

    // Compatibility with React.js as of January 12, 2022:
    // https://github.com/facebook/react/blob/c09596cc6021e1f9f8a88179add93f80fc07823b/packages/react-dom/src/shared/possibleStandardNames.js
    static constexpr char attribute_names[] =
        // List based on React.js (react-dom) as of January 12, 2022:
        // https://github.com/facebook/react/blob/c09596cc6021e1f9f8a88179add93f80fc07823b/packages/react-dom/src/events/EventRegistry.js
        "onAbort\0"
        "onAbortCapture\0"
        "onAnimationEnd\0"
        "onAnimationEndCapture\0"
        "onAnimationIteration\0"
        "onAnimationIterationCapture\0"
        "onAnimationStart\0"
        "onAnimationStartCapture\0"
        "onAuxClick\0"
        "onAuxClickCapture\0"
        "onBeforeInput\0"
        "onBeforeInputCapture\0"
        "onBlur\0"
        "onBlurCapture\0"
        "onCanPlay\0"
        "onCanPlayCapture\0"
        "onCanPlayThrough\0"
        "onCanPlayThroughCapture\0"
        "onCancel\0"
        "onCancelCapture\0"
        "onChange\0"
        "onChangeCapture\0"
        "onClick\0"
        "onClickCapture\0"
        "onClose\0"
        "onCloseCapture\0"
        "onCompositionEnd\0"
        "onCompositionEndCapture\0"
        "onCompositionStart\0"
        "onCompositionStartCapture\0"
        "onCompositionUpdate\0"
        "onCompositionUpdateCapture\0"
        "onContextMenu\0"
        "onContextMenuCapture\0"
        "onCopy\0"
        "onCopyCapture\0"
        "onCut\0"
        "onCutCapture\0"
        "onDoubleClick\0"
        "onDoubleClickCapture\0"
        "onDrag\0"
        "onDragCapture\0"
        "onDragEnd\0"
        "onDragEndCapture\0"
        "onDragEnter\0"
        "onDragEnterCapture\0"
        "onDragExit\0"
        "onDragExitCapture\0"
        "onDragLeave\0"
        "onDragLeaveCapture\0"
        "onDragOver\0"
        "onDragOverCapture\0"
        "onDragStart\0"
        "onDragStartCapture\0"
        "onDrop\0"
        "onDropCapture\0"
        "onDurationChange\0"
        "onDurationChangeCapture\0"
        "onEmptied\0"
        "onEmptiedCapture\0"
        "onEncrypted\0"
        "onEncryptedCapture\0"
        "onEnded\0"
        "onEndedCapture\0"
        "onError\0"
        "onErrorCapture\0"
        "onFocus\0"
        "onFocusCapture\0"
        "onGotPointerCapture\0"
        "onGotPointerCaptureCapture\0"
        "onInput\0"
        "onInputCapture\0"
        "onInvalid\0"
        "onInvalidCapture\0"
        "onKeyDown\0"
        "onKeyDownCapture\0"
        "onKeyPress\0"
        "onKeyPressCapture\0"
        "onKeyUp\0"
        "onKeyUpCapture\0"
        "onLoad\0"
        "onLoadCapture\0"
        "onLoadStart\0"
        "onLoadStartCapture\0"
        "onLoadedData\0"
        "onLoadedDataCapture\0"
        "onLoadedMetadata\0"
        "onLoadedMetadataCapture\0"
        "onLostPointerCapture\0"
        "onLostPointerCaptureCapture\0"
        "onMouseDown\0"
        "onMouseDownCapture\0"
        "onMouseEnter\0"
        "onMouseLeave\0"
        "onMouseMove\0"
        "onMouseMoveCapture\0"
        "onMouseOut\0"
        "onMouseOutCapture\0"
        "onMouseOver\0"
        "onMouseOverCapture\0"
        "onMouseUp\0"
        "onMouseUpCapture\0"
        "onPaste\0"
        "onPasteCapture\0"
        "onPause\0"
        "onPauseCapture\0"
        "onPlay\0"
        "onPlayCapture\0"
        "onPlaying\0"
        "onPlayingCapture\0"
        "onPointerCancel\0"
        "onPointerCancelCapture\0"
        "onPointerDown\0"
        "onPointerDownCapture\0"
        "onPointerEnter\0"
        "onPointerLeave\0"
        "onPointerMove\0"
        "onPointerMoveCapture\0"
        "onPointerOut\0"
        "onPointerOutCapture\0"
        "onPointerOver\0"
        "onPointerOverCapture\0"
        "onPointerUp\0"
        "onPointerUpCapture\0"
        "onProgress\0"
        "onProgressCapture\0"
        "onRateChange\0"
        "onRateChangeCapture\0"
        "onReset\0"
        "onResetCapture\0"
        "onResize\0"
        "onResizeCapture\0"
        "onScroll\0"
        "onScrollCapture\0"
        "onSeeked\0"
        "onSeekedCapture\0"
        "onSeeking\0"
        "onSeekingCapture\0"
        "onSelect\0"
        "onSelectCapture\0"
        "onStalled\0"
        "onStalledCapture\0"
        "onSubmit\0"
        "onSubmitCapture\0"
        "onSuspend\0"
        "onSuspendCapture\0"
        "onTimeUpdate\0"
        "onTimeUpdateCapture\0"
        "onToggle\0"
        "onToggleCapture\0"
        "onTouchCancel\0"
        "onTouchCancelCapture\0"
        "onTouchEnd\0"
        "onTouchEndCapture\0"
        "onTouchMove\0"
        "onTouchMoveCapture\0"
        "onTouchStart\0"
        "onTouchStartCapture\0"
        "onTransitionEnd\0"
        "onTransitionEndCapture\0"
        "onVolumeChange\0"
        "onVolumeChangeCapture\0"
        "onWaiting\0"
        "onWaitingCapture\0"
        "onWheel\0"
        "onWheelCapture\0"

        // Compatibility with React.js as of January 12, 2022:
        // https://github.com/facebook/react/blob/c09596cc6021e1f9f8a88179add93f80fc07823b/packages/react-dom/src/shared/possibleStandardNames.js
        "accentHeight\0"
        "acceptCharset\0"
        "accessKey\0"
        "alignmentBaseline\0"
        "allowFullScreen\0"
        "allowReorder\0"
        "arabicForm\0"
        "attributeName\0"
        "attributeType\0"
        "autoCapitalize\0"
        "autoComplete\0"
        "autoCorrect\0"
        "autoFocus\0"
        "autoPlay\0"
        "autoReverse\0"
        "autoSave\0"
        "baseFrequency\0"
        "baseProfile\0"
        "baselineShift\0"
        "calcMode\0"
        "capHeight\0"
        "cellPadding\0"
        "cellSpacing\0"
        "charSet\0"
        "classID\0"
        "className\0"
        "clipPath\0"
        "clipPathUnits\0"
        "clipRule\0"
        "colSpan\0"
        "colorInterpolation\0"
        "colorInterpolationFilters\0"
        "colorProfile\0"
        "colorRendering\0"
        "contentEditable\0"
        "contentScriptType\0"
        "contentStyleType\0"
        "contextMenu\0"
        "controlsList\0"
        "crossOrigin\0"
        "dangerouslySetInnerHTML\0"
        "dateTime\0"
        "defaultChecked\0"
        "defaultValue\0"
        "diffuseConstant\0"
        "disablePictureInPicture\0"
        "disableRemotePlayback\0"
        "dominantBaseline\0"
        "edgeMode\0"
        "enableBackground\0"
        "encType\0"
        "enterKeyHint\0"
        "externalResourcesRequired\0"
        "fillOpacity\0"
        "fillRule\0"
        "filterRes\0"
        "filterUnits\0"
        "floodColor\0"
        "floodOpacity\0"
        "fontFamily\0"
        "fontSize\0"
        "fontSizeAdjust\0"
        "fontStretch\0"
        "fontStyle\0"
        "fontVariant\0"
        "fontWeight\0"
        "formAction\0"
        "formEncType\0"
        "formMethod\0"
        "formNoValidate\0"
        "formTarget\0"
        "frameBorder\0"
        "glyphName\0"
        "glyphOrientationHorizontal\0"
        "glyphOrientationVertical\0"
        "glyphRef\0"
        "gradientTransform\0"
        "gradientUnits\0"
        "horizAdvX\0"
        "horizOriginX\0"
        "hrefLang\0"
        "htmlFor\0"
        "httpEquiv\0"
        "imageRendering\0"
        "imageSizes\0"
        "imageSrcSet\0"
        "innerHTML\0"
        "inputMode\0"
        "itemID\0"
        "itemProp\0"
        "itemRef\0"
        "itemScope\0"
        "itemType\0"
        "kernelMatrix\0"
        "kernelUnitLength\0"
        "keyParams\0"
        "keyPoints\0"
        "keySplines\0"
        "keyTimes\0"
        "keyType\0"
        "lengthAdjust\0"
        "letterSpacing\0"
        "lightingColor\0"
        "limitingConeAngle\0"
        "marginHeight\0"
        "marginWidth\0"
        "markerEnd\0"
        "markerHeight\0"
        "markerMid\0"
        "markerStart\0"
        "markerUnits\0"
        "markerWidth\0"
        "maskContentUnits\0"
        "maskUnits\0"
        "maxLength\0"
        "mediaGroup\0"
        "minLength\0"
        "noModule\0"
        "noValidate\0"
        "numOctaves\0"
        "overlinePosition\0"
        "overlineThickness\0"
        "paintOrder\0"
        "pathLength\0"
        "patternContentUnits\0"
        "patternTransform\0"
        "patternUnits\0"
        "playsInline\0"
        "pointerEvents\0"
        "pointsAtX\0"
        "pointsAtY\0"
        "pointsAtZ\0"
        "preserveAlpha\0"
        "preserveAspectRatio\0"
        "primitiveUnits\0"
        "radioGroup\0"
        "readOnly\0"
        "refX\0"
        "refY\0"
        "referrerPolicy\0"
        "renderingIntent\0"
        "repeatCount\0"
        "repeatDur\0"
        "requiredExtensions\0"
        "requiredFeatures\0"
        "rowSpan\0"
        "shapeRendering\0"
        "specularConstant\0"
        "specularExponent\0"
        "spellCheck\0"
        "spreadMethod\0"
        "srcDoc\0"
        "srcLang\0"
        "srcSet\0"
        "startOffset\0"
        "stdDeviation\0"
        "stitchTiles\0"
        "stopColor\0"
        "stopOpacity\0"
        "strikethroughPosition\0"
        "strikethroughThickness\0"
        "strokeDasharray\0"
        "strokeDashoffset\0"
        "strokeLinecap\0"
        "strokeLinejoin\0"
        "strokeMiterlimit\0"
        "strokeOpacity\0"
        "strokeWidth\0"
        "suppressContentEditableWarning\0"
        "suppressHydrationWarning\0"
        "surfaceScale\0"
        "systemLanguage\0"
        "tabIndex\0"
        "tableValues\0"
        "targetX\0"
        "targetY\0"
        "textAnchor\0"
        "textDecoration\0"
        "textLength\0"
        "textRendering\0"
        "underlinePosition\0"
        "underlineThickness\0"
        "unicodeBidi\0"
        "unicodeRange\0"
        "unitsPerEm\0"
        "useMap\0"
        "vAlphabetic\0"
        "vHanging\0"
        "vIdeographic\0"
        "vMathematical\0"
        "vectorEffect\0"
        "vertAdvY\0"
        "vertOriginX\0"
        "vertOriginY\0"
        "viewBox\0"
        "viewTarget\0"
        "wordSpacing\0"
        "writingMode\0"
        "xChannelSelector\0"
        "xHeight\0"
        "xlinkActuate\0"
        "xlinkArcrole\0"
        "xlinkHref\0"
        "xlinkRole\0"
        "xlinkShow\0"
        "xlinkTitle\0"
        "xlinkType\0"
        "xmlBase\0"
        "xmlLang\0"
        "xmlSpace\0"
        "xmlnsXlink\0"
        "yChannelSelector\0"
        "zoomAndPan\0"
        "\0";
    for (std::string_view raw_attribute_name :
         c_string_list_view(attribute_names)) {
      string8_view attribute_name = to_string8_view(raw_attribute_name);
      char8* lowered_attribute_name =
          string_allocator.allocate_uninitialized_array<char8>(
              attribute_name.size());
      std::transform(attribute_name.begin(), attribute_name.end(),
                     lowered_attribute_name, tolower);
      auto [_it, inserted] = aliases.try_emplace(
          string8_view(lowered_attribute_name, attribute_name.size()),
          jsx_attribute{attribute_name});
      QLJS_ASSERT(inserted);
    }

    return aliases;
  }();
  return cache;
}
}

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
