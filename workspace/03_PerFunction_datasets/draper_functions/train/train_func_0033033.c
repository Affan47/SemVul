addFloatx80Sigs(floatx80 a, floatx80 b, int zSign, float_status_t &status)
{
    Bit32s aExp, bExp, zExp;
    Bit64u aSig, bSig, zSig0, zSig1;


    if (floatx80_is_unsupported(a) || floatx80_is_unsupported(b))
    {
        float_raise(status, float_flag_invalid);
        return floatx80_default_nan;
    }

    aSig = extractFloatx80Frac(a);
    aExp = extractFloatx80Exp(a);
    bSig = extractFloatx80Frac(b);
    bExp = extractFloatx80Exp(b);

    if (aExp == 0x7FFF) {
        if ((Bit64u) (aSig<<1) || ((bExp == 0x7FFF) && (Bit64u) (bSig<<1)))
            return propagateFloatx80NaN(a, b, status);
        if (bSig && (bExp == 0)) float_raise(status, float_flag_denormal);
        return a;
    }
    if (bExp == 0x7FFF) {
        if ((Bit64u) (bSig<<1)) return propagateFloatx80NaN(a, b, status);
        if (aSig && (aExp == 0)) float_raise(status, float_flag_denormal);
        return packFloatx80(zSign, 0x7FFF, BX_CONST64(0x8000000000000000));
    }
    if (aExp == 0) {
        if (aSig == 0) {
            if ((bExp == 0) && bSig) {
                float_raise(status, float_flag_denormal);
                normalizeFloatx80Subnormal(bSig, &bExp, &bSig);
            }
            return roundAndPackFloatx80(get_float_rounding_precision(status),
                    zSign, bExp, bSig, 0, status);
        }
        float_raise(status, float_flag_denormal);
        normalizeFloatx80Subnormal(aSig, &aExp, &aSig);
    }
    if (bExp == 0) {
        if (bSig == 0)
            return roundAndPackFloatx80(get_float_rounding_precision(status),
                    zSign, aExp, aSig, 0, status);

        float_raise(status, float_flag_denormal);
        normalizeFloatx80Subnormal(bSig, &bExp, &bSig);
    }
    Bit32s expDiff = aExp - bExp;
    zExp = aExp;
    if (0 < expDiff) {
        shift64ExtraRightJamming(bSig, 0,  expDiff, &bSig, &zSig1);
    }
    else if (expDiff < 0) {
        shift64ExtraRightJamming(aSig, 0, -expDiff, &aSig, &zSig1);
        zExp = bExp;
    }
    else {
        zSig0 = aSig + bSig;
        zSig1 = 0;
        goto shiftRight1;
    }
    zSig0 = aSig + bSig;
    if ((Bit64s) zSig0 < 0) goto roundAndPack;
 shiftRight1:
    shift64ExtraRightJamming(zSig0, zSig1, 1, &zSig0, &zSig1);
    zSig0 |= BX_CONST64(0x8000000000000000);
    zExp++;
 roundAndPack:
    return
        roundAndPackFloatx80(get_float_rounding_precision(status),
            zSign, zExp, zSig0, zSig1, status);
}
