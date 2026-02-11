mapBackgroundSize(BackgroundLayer* layer, CSSValueImpl* value)
{
    LengthSize b = RenderStyle::initialBackgroundSize();

    if (value->cssValueType() == CSSValue::CSS_INITIAL) {
        layer->setBackgroundSize(b);
        return;
    }

    if (!value->isPrimitiveValue())
        return;

    CSSPrimitiveValueImpl* primitiveValue = static_cast<CSSPrimitiveValueImpl*>(value);
    int id = primitiveValue->getIdent();
    if (id == CSS_VAL_CONTAIN || id == CSS_VAL_COVER) {
        layer->setBackgroundSizeType( (id ==  CSS_VAL_CONTAIN) ? BGSCONTAIN : BGSCOVER );
        return;
    }

    PairImpl* pair = primitiveValue->getPairValue();
    if (!pair)
        return;

    CSSPrimitiveValueImpl* first = static_cast<CSSPrimitiveValueImpl*>(pair->first());
    CSSPrimitiveValueImpl* second = static_cast<CSSPrimitiveValueImpl*>(pair->second());

    if (!first || !second)
        return;

    Length firstLength, secondLength;
    int firstType = first->primitiveType();
    int secondType = second->primitiveType();

    if (firstType == CSSPrimitiveValue::CSS_UNKNOWN)
        firstLength = Length(Auto);
    else if (firstType > CSSPrimitiveValue::CSS_PERCENTAGE && firstType < CSSPrimitiveValue::CSS_DEG)
        firstLength = Length(first->computeLength(style, logicalDpiY), Fixed);
    else if (firstType == CSSPrimitiveValue::CSS_PERCENTAGE)
        firstLength = Length(first->floatValue(CSSPrimitiveValue::CSS_PERCENTAGE), Percent);
    else
        return;

    if (secondType == CSSPrimitiveValue::CSS_UNKNOWN)
        secondLength = Length(Auto);
    else if (secondType > CSSPrimitiveValue::CSS_PERCENTAGE && secondType < CSSPrimitiveValue::CSS_DEG)
        secondLength = Length(second->computeLength(style, logicalDpiY), Fixed);
    else if (secondType == CSSPrimitiveValue::CSS_PERCENTAGE)
        secondLength = Length(second->floatValue(CSSPrimitiveValue::CSS_PERCENTAGE), Percent);
    else
        return;

    b.width = firstLength;
    b.height = secondLength;
    layer->setBackgroundSize(b);
}
