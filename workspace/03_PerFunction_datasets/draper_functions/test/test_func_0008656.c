mono_decimalRound(decimal_repr* pA, gint32 decimals)
{
    guint64 alo, ahi;
    int scale, sign;

    MONO_ARCH_SAVE_REGS;

    DECTO128(pA, alo, ahi);
    scale = pA->signscale.scale;
    sign = pA->signscale.sign;
    if (scale > decimals) {
        div128DecadeFactor(&alo, &ahi, scale - decimals);
        scale = decimals;
    }

    pack128toDecimal(pA, alo, ahi, scale, sign);
}
