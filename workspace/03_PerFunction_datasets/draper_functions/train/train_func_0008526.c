cvt_ll(SprintfState *ss, JSInt64 num, int width, int prec, int radix,
                  int type, int flags, const char *hexp)
{
    char cvtbuf[100];
    char *cvt;
    int digits;
    JSInt64 rad;


    if ((prec == 0) && (JSLL_IS_ZERO(num))) {
        return 0;
    }


    JSLL_I2L(rad, radix);
    cvt = cvtbuf + sizeof(cvtbuf);
    digits = 0;
    while (!JSLL_IS_ZERO(num)) {
        JSInt32 digit;
        JSInt64 quot, rem;
        JSLL_UDIVMOD(&quot, &rem, num, rad);
        JSLL_L2I(digit, rem);
        *--cvt = hexp[digit & 0xf];
        digits++;
        num = quot;
    }
    if (digits == 0) {
        *--cvt = '0';
        digits++;
    }


    return fill_n(ss, cvt, digits, width, prec, type, flags);
}
