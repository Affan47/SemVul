operator/(const SignExtendedNumber& a) const
{


    if (a.value == 0)
    {
        if (a.negative)
            return SignExtendedNumber(value == 0 && negative);
        else
            return extreme(negative);
    }

    uinteger_t aAbs = copySign(a.value, a.negative);
    uinteger_t rvVal;

    if (!isMinimum())
        rvVal = copySign(value, negative) / aAbs;


    else if (aAbs & (aAbs-1))
        rvVal = UINT64_MAX / aAbs;

    else
    {
        if (aAbs == 1)
            return extreme(!a.negative);
        rvVal = 1ULL << 63;
        aAbs >>= 1;
        if (aAbs & 0xAAAAAAAAAAAAAAAAULL) rvVal >>= 1;
        if (aAbs & 0xCCCCCCCCCCCCCCCCULL) rvVal >>= 2;
        if (aAbs & 0xF0F0F0F0F0F0F0F0ULL) rvVal >>= 4;
        if (aAbs & 0xFF00FF00FF00FF00ULL) rvVal >>= 8;
        if (aAbs & 0xFFFF0000FFFF0000ULL) rvVal >>= 16;
        if (aAbs & 0xFFFFFFFF00000000ULL) rvVal >>= 32;
    }
    bool rvNeg = negative != a.negative;
    rvVal = copySign(rvVal, rvNeg);

    return SignExtendedNumber(rvVal, rvVal != 0 && rvNeg);
}
