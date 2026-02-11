mono_decimal2Int64(decimal_repr* pA, gint64* pResult)
{
    guint64 alo, ahi;
    int sign, scale;

    MONO_ARCH_SAVE_REGS;

    DECTO128(pA, alo, ahi);
    scale = pA->signscale.scale;
    if (scale > 0) {
        div128DecadeFactor(&alo, &ahi, scale);
    }

    if (ahi != 0) return DECIMAL_OVERFLOW;

    sign = pA->signscale.sign;
    if (sign && alo != 0) {
        if (alo > LIT_GUINT64_HIGHBIT) return DECIMAL_OVERFLOW;
        *pResult = (gint64) ~(alo-1);
    } else {
        if (alo & LIT_GUINT64_HIGHBIT) return DECIMAL_OVERFLOW;
        *pResult = (gint64) alo;
    }

    return DECIMAL_SUCCESS;
}
