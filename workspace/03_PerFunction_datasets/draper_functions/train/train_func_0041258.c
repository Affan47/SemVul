floatx80_compare_quiet(floatx80 a, floatx80 b, float_status_t &status)
{
    float_class_t aClass = floatx80_class(a);
    float_class_t bClass = floatx80_class(b);

    if (aClass == float_NaN || bClass == float_NaN)
    {
        if (floatx80_is_unsupported(a) || floatx80_is_unsupported(b))
            float_raise(status, float_flag_invalid);

        if (floatx80_is_signaling_nan(a) || floatx80_is_signaling_nan(b))
            float_raise(status, float_flag_invalid);

        return float_relation_unordered;
    }

    if (aClass == float_denormal || bClass == float_denormal)
    {
        float_raise(status, float_flag_denormal);
    }

    int aSign = extractFloatx80Sign(a);
    int bSign = extractFloatx80Sign(b);

    if (aClass == float_zero) {
        if (bClass == float_zero) return float_relation_equal;
        return bSign ? float_relation_greater : float_relation_less;
    }

    if (bClass == float_zero || aSign != bSign) {
        return aSign ? float_relation_less : float_relation_greater;
    }

    Bit64u aSig = extractFloatx80Frac(a);
    Bit32s aExp = extractFloatx80Exp(a);
    Bit64u bSig = extractFloatx80Frac(b);
    Bit32s bExp = extractFloatx80Exp(b);

    if (aClass == float_denormal)
        normalizeFloatx80Subnormal(aSig, &aExp, &aSig);

    if (bClass == float_denormal)
        normalizeFloatx80Subnormal(bSig, &bExp, &bSig);

    if (aExp == bExp && aSig == bSig)
        return float_relation_equal;

    int less_than =
        aSign ? ((bExp < aExp) || ((bExp == aExp) && (bSig < aSig)))
              : ((aExp < bExp) || ((aExp == bExp) && (aSig < bSig)));

    if (less_than) return float_relation_less;
    return float_relation_greater;
}
