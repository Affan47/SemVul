float64_to_int64(float64 a, float_status_t &status)
{
    int aSign;
    Bit16s aExp;
    Bit64u aSig, aSigExtra;

    aSig = extractFloat64Frac(a);
    aExp = extractFloat64Exp(a);
    aSign = extractFloat64Sign(a);
    if (aExp) aSig |= BX_CONST64(0x0010000000000000);
    int shiftCount = 0x433 - aExp;
    if (shiftCount <= 0) {
        if (0x43E < aExp) {
            float_raise(status, float_flag_invalid);
            return (Bit64s)(int64_indefinite);
        }
        aSigExtra = 0;
        aSig <<= -shiftCount;
    }
    else {
        shift64ExtraRightJamming(aSig, 0, shiftCount, &aSig, &aSigExtra);
    }
    return roundAndPackInt64(aSign, aSig, aSigExtra, status);
}
