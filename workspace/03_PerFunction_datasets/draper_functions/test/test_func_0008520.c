floatx80_to_float32(floatx80 a, float_status_t &status)
{
    Bit64u aSig = extractFloatx80Frac(a);
    Bit32s aExp = extractFloatx80Exp(a);
    int aSign = extractFloatx80Sign(a);


    if (floatx80_is_unsupported(a))
    {
        float_raise(status, float_flag_invalid);
        return float32_default_nan;
    }

    if (aExp == 0x7FFF) {
        if ((Bit64u) (aSig<<1))
            return commonNaNToFloat32(floatx80ToCommonNaN(a, status));

        return packFloat32(aSign, 0xFF, 0);
    }
    aSig = shift64RightJamming(aSig, 33);
    if (aExp || aSig) aExp -= 0x3F81;
    return roundAndPackFloat32(aSign, aExp, (Bit32u) aSig, status);
}
