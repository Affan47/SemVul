floatx80_to_int32(floatx80 a, float_status_t &status)
{
    Bit64u aSig = extractFloatx80Frac(a);
    Bit32s aExp = extractFloatx80Exp(a);
    int aSign = extractFloatx80Sign(a);


    if (floatx80_is_unsupported(a))
    {
        float_raise(status, float_flag_invalid);
        return int32_indefinite;
    }

    if ((aExp == 0x7FFF) && (Bit64u) (aSig<<1)) aSign = 0;
    int shiftCount = 0x4037 - aExp;
    if (shiftCount <= 0) shiftCount = 1;
    aSig = shift64RightJamming(aSig, shiftCount);
    return roundAndPackInt32(aSign, aSig, status);
}
