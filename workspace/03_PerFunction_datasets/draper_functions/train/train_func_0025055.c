calculateBaselineShift(RenderObject* item)
{
    const Font& font = item->style()->htmlFont();
    const SVGRenderStyle* svgStyle = item->style()->svgStyle();

    float baselineShift = 0.0f;
    if (svgStyle->baselineShift() == BS_LENGTH) {
        CSSPrimitiveValueImpl* primitive = static_cast<CSSPrimitiveValueImpl*>(svgStyle->baselineShiftValue());
        baselineShift = primitive->floatValue();


    } else {
        float baselineAscent = font.ascent() + font.descent();

        switch (svgStyle->baselineShift()) {
        case BS_BASELINE:
            break;
        case BS_SUB:
            baselineShift = -baselineAscent / 2.0f;
            break;
        case BS_SUPER:
            baselineShift = baselineAscent / 2.0f;
            break;
        default:
            ASSERT_NOT_REACHED();
        }
    }

    return baselineShift;
}
