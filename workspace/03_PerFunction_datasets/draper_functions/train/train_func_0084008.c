float64_to_int32_round_to_zero(float64 a, float_status_t &status)
{
    int aSign;
    Bit16s aExp;
    Bit64u aSig, savedASig;
    Bit32s z;
    int shiftCount;

    aSig = extractFloat64Frac(a);
    aExp = extractFloat64Exp(a);
    aSign = extractFloat64Sign(a);
    if (0x41E < aExp) {
        if ((aExp == 0x7FF) && aSig) aSign = 0;
        goto invalid;
    }
    else if (aExp < 0x3FF) {
        if (aExp || aSig) float_raise(status, float_flag_inexact);
        return 0;
    }
    aSig |= BX_CONST64(0x0010000000000000);
    shiftCount = 0x433 - aExp;
    savedASig = aSig;
    aSig >>= shiftCount;
    z = (Bit32s) aSig;
    if (aSign) z = -z;
    if ((z < 0) ^ aSign) {
 invalid:
        float_raise(status, float_flag_invalid);
        return (Bit32s)(int32_indefinite);
    }
    if ((aSig<<shiftCount) != savedASig) {
        float_raise(status, float_flag_inexact);
    }
    return z;
}
