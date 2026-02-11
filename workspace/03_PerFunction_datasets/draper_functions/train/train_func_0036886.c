set(double source, int32_t maximumDigits, UBool fixedPoint)
{

    char rep[MAX_DIGITS + 8];
    char *digitPtr      = fDigits;
    char *repPtr        = rep + 2;
    int32_t exponent    = 0;

    fIsPositive = !uprv_isNegative(source);


    sprintf(rep, "%+1.*e", MAX_DBL_DIGITS - 1, source);
    fDecimalAt  = 0;
    rep[2]      = rep[1];

    while (*repPtr == kZero) {
        repPtr++;
        fDecimalAt--;
    }

    while (*repPtr != 'e') {
        *(digitPtr++) = *(repPtr++);
    }
    fCount = MAX_DBL_DIGITS + fDecimalAt;


    UBool negExp = (*(++repPtr) == '-');
    while (*(++repPtr) != 0) {
        exponent = 10*exponent + *repPtr - kZero;
    }
    if (negExp) {
        exponent = -exponent;
    }
    fDecimalAt += exponent + 1;


    if (fixedPoint && -fDecimalAt >= maximumDigits)
    {


        if (-fDecimalAt == maximumDigits && shouldRoundUp(0)) {
            fCount = 1;
            ++fDecimalAt;
            fDigits[0] = (char)'1';
        } else {


            fCount = 0;
        }
        return;
    }


    if (fixedPoint || (0 < maximumDigits && maximumDigits < fCount)) {
        round(fixedPoint ? (maximumDigits + fDecimalAt) : maximumDigits);
    }
    else {

        while (fCount > 1 && fDigits[fCount - 1] == kZero)
            --fCount;
    }
}
