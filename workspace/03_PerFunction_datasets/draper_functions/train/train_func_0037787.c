validUnit( Value *value, int unitflags, bool strict )
{
    if ( unitflags & FNonNeg && value->fValue < 0 )
        return false;

    bool b = false;
    switch( value->unit ) {
    case CSSPrimitiveValue::CSS_NUMBER:
        b = (unitflags & FNumber);
        if ( !b && ( (unitflags & FLength) && (value->fValue == 0 || !strict ) ) ) {
            value->unit = CSSPrimitiveValue::CSS_PX;
            b = true;
        }
        if (!b && (unitflags & FInteger) && value->isInt)
            b = true;
        break;
    case CSSPrimitiveValue::CSS_PERCENTAGE:
        b = (unitflags & FPercent);
        break;
    case Value::Q_EMS:
    case CSSPrimitiveValue::CSS_EMS:
    case CSSPrimitiveValue::CSS_EXS:
    case CSSPrimitiveValue::CSS_PX:
    case CSSPrimitiveValue::CSS_CM:
    case CSSPrimitiveValue::CSS_MM:
    case CSSPrimitiveValue::CSS_IN:
    case CSSPrimitiveValue::CSS_PT:
    case CSSPrimitiveValue::CSS_PC:
        b = (unitflags & FLength);
        break;
    case CSSPrimitiveValue::CSS_MS:
    case CSSPrimitiveValue::CSS_S:
        b = (unitflags & FTime);
        break;
    case CSSPrimitiveValue::CSS_DEG:
    case CSSPrimitiveValue::CSS_RAD:
    case CSSPrimitiveValue::CSS_GRAD:
    case CSSPrimitiveValue::CSS_HZ:
    case CSSPrimitiveValue::CSS_KHZ:
    case CSSPrimitiveValue::CSS_DPI:
    case CSSPrimitiveValue::CSS_DPCM:
    case CSSPrimitiveValue::CSS_DIMENSION:
    default:
        break;
    }
    return b;
}
