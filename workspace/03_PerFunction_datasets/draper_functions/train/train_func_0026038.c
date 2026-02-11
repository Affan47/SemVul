numberValue(CSSValueImpl* value, float& result)
{
    if (value->isPrimitiveValue()
        && static_cast<CSSPrimitiveValueImpl*>(value)->primitiveType() == CSSPrimitiveValue::CSS_NUMBER) {
        result = static_cast<CSSPrimitiveValueImpl*>(value)->floatValue(CSSPrimitiveValue::CSS_NUMBER);
        return true;
    }
    return false;
}
