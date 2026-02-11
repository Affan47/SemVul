regcomp( const char *exp )
{
    register regexp *r;
    register char *scan;
    register char *longest;
    register unsigned len;
    int flags;

    if (exp == NULL)
        FAIL("NULL argument");


#ifdef notdef
    if (exp[0] == '.' && exp[1] == '*') exp += 2;
#endif
    regparse = (char *)exp;
    regnpar = 1;
    regsize = 0L;
    regcode = &regdummy;
    regc(MAGIC);
    if (reg(0, &flags) == NULL)
        return(NULL);


    if (regsize >= 32767L)
        FAIL("regexp too big");


    r = (regexp *)BJAM_MALLOC(sizeof(regexp) + (unsigned)regsize);
    if (r == NULL)
        FAIL("out of space");


    regparse = (char *)exp;
    regnpar = 1;
    regcode = r->program;
    regc(MAGIC);
    if (reg(0, &flags) == NULL)
        return(NULL);


    r->regstart = '\0';
    r->reganch = 0;
    r->regmust = NULL;
    r->regmlen = 0;
    scan = r->program+1;
    if (OP(regnext(scan)) == END) {
        scan = OPERAND(scan);


        if (OP(scan) == EXACTLY)
            r->regstart = *OPERAND(scan);
        else if (OP(scan) == BOL)
            r->reganch++;


        if (flags&SPSTART) {
            longest = NULL;
            len = 0;
            for (; scan != NULL; scan = regnext(scan))
                if (OP(scan) == EXACTLY && strlen(OPERAND(scan)) >= len) {
                    longest = OPERAND(scan);
                    len = strlen(OPERAND(scan));
                }
            r->regmust = longest;
            r->regmlen = len;
        }
    }

    return(r);
}
