float32_to_float64(float32 a, float_status_t &status)
{
    Bit32u aSig = extractFloat32Frac(a);
    Bit16s aExp = extractFloat32Exp(a);
    int  aSign = extractFloat32Sign(a);

    if (aExp == 0xFF) {
        if (aSig) return commonNaNToFloat64(float32ToCommonNaN(a, status));
        return packFloat64(aSign, 0x7FF, 0);
    }
    if (aExp == 0) {
        if (aSig == 0) return packFloat64(aSign, 0, 0);
        float_raise(status, float_flag_denormal);
        normalizeFloat32Subnormal(aSig, &aExp, &aSig);
        --aExp;
    }
    return packFloat64(aSign, aExp + 0x380, ((Bit64u) aSig)<<29);
}
