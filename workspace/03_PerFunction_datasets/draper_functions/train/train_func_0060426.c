floatx80_to_int64_round_to_zero(floatx80 a, float_status_t &status)
{
    int aSign;
    Bit32s aExp;
    Bit64u aSig;
    Bit64s z;


    if (floatx80_is_unsupported(a))
    {
        float_raise(status, float_flag_invalid);
        return int64_indefinite;
    }

    aSig = extractFloatx80Frac(a);
    aExp = extractFloatx80Exp(a);
    aSign = extractFloatx80Sign(a);
    int shiftCount = aExp - 0x403E;
    if (0 <= shiftCount) {
        aSig &= BX_CONST64(0x7FFFFFFFFFFFFFFF);
        if ((a.exp != 0xC03E) || aSig) {
            float_raise(status, float_flag_invalid);
        }
        return (Bit64s)(int64_indefinite);
    }
    else if (aExp < 0x3FFF) {
        if (aExp | aSig) float_raise(status, float_flag_inexact);
        return 0;
    }
    z = aSig>>(-shiftCount);
    if ((Bit64u) (aSig<<(shiftCount & 63))) {
        float_raise(status, float_flag_inexact);
    }
    if (aSign) z = -z;
    return z;
}
