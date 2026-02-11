floatx80_round_to_int(floatx80 a, float_status_t &status)
{
    int aSign;
    Bit64u lastBitMask, roundBitsMask;
    Bit8u roundingMode;
    floatx80 z;


    if (floatx80_is_unsupported(a))
    {
        float_raise(status, float_flag_invalid);
        return floatx80_default_nan;
    }

    Bit32s aExp = extractFloatx80Exp(a);
    Bit64u aSig = extractFloatx80Frac(a);
    if (0x403E <= aExp) {
        if ((aExp == 0x7FFF) && (Bit64u) (aSig<<1)) {
            return propagateFloatx80NaN(a, status);
        }
        return a;
    }
    if (aExp < 0x3FFF) {
        if (aExp == 0) {
            if ((aSig<<1) == 0) return a;
            float_raise(status, float_flag_denormal);
        }
        float_raise(status, float_flag_inexact);
        aSign = extractFloatx80Sign(a);
        switch (get_float_rounding_mode(status)) {
         case float_round_nearest_even:
            if ((aExp == 0x3FFE) && (Bit64u) (aSig<<1)) {
                set_float_rounding_up(status);
                return packFloatx80(aSign, 0x3FFF, BX_CONST64(0x8000000000000000));
            }
            break;
         case float_round_down:
            if (aSign) {
                set_float_rounding_up(status);
                return packFloatx80(1, 0x3FFF, BX_CONST64(0x8000000000000000));
            }
            else {
                return packFloatx80(0, 0, 0);
            }
         case float_round_up:
            if (aSign) {
                return packFloatx80(1, 0, 0);
            }
            else {
                set_float_rounding_up(status);
                return packFloatx80(0, 0x3FFF, BX_CONST64(0x8000000000000000));
            }
        }
        return packFloatx80(aSign, 0, 0);
    }
    lastBitMask = 1;
    lastBitMask <<= 0x403E - aExp;
    roundBitsMask = lastBitMask - 1;
    z = a;
    roundingMode = get_float_rounding_mode(status);
    if (roundingMode == float_round_nearest_even) {
        z.fraction += lastBitMask>>1;
        if ((z.fraction & roundBitsMask) == 0) z.fraction &= ~lastBitMask;
    }
    else if (roundingMode != float_round_to_zero) {
        if (extractFloatx80Sign(z) ^ (roundingMode == float_round_up))
            z.fraction += roundBitsMask;
    }
    z.fraction &= ~roundBitsMask;
    if (z.fraction == 0) {
        z.exp++;
        z.fraction = BX_CONST64(0x8000000000000000);
    }
    if (z.fraction != a.fraction) {
        float_raise(status, float_flag_inexact);
        if (z.fraction > a.fraction || z.exp > a.exp)
            set_float_rounding_up(status);
    }
    return z;
}
