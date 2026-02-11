DaylightSavingTA(jsdouble t)
{
    volatile int64 PR_t;
    int64 ms2us;
    int64 offset;
    jsdouble result;


    if (JSDOUBLE_IS_NaN(t))
        return t;


    if (t < 0.0 || t > 2145916800000.0) {
        jsint year;
        jsdouble day;

        year = EquivalentYearForDST(YearFromTime(t));
        day = MakeDay(year, MonthFromTime(t), DateFromTime(t));
        t = MakeDate(day, TimeWithinDay(t));
    }


    JSLL_D2L(PR_t, t);
    JSLL_I2L(ms2us, PRMJ_USEC_PER_MSEC);
    JSLL_MUL(PR_t, PR_t, ms2us);

    offset = PRMJ_DSTOffset(PR_t);

    JSLL_DIV(offset, offset, ms2us);
    JSLL_L2D(result, offset);
    return result;
}
