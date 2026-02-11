JimParseExprNumber(struct JimParserCtx *pc)
{
    int allowdot = 1;
    int base = 10;


    pc->tt = JIM_TT_EXPR_INT;
    pc->tstart = pc->p;
    pc->tline = pc->linenr;


    if (pc->p[0] == '0') {
        switch (pc->p[1]) {
            case 'x':
            case 'X':
                base = 16;
                allowdot = 0;
                pc->p += 2;
                pc->len -= 2;
                break;
            case 'o':
            case 'O':
                base = 8;
                allowdot = 0;
                pc->p += 2;
                pc->len -= 2;
                break;
            case 'b':
            case 'B':
                base = 2;
                allowdot = 0;
                pc->p += 2;
                pc->len -= 2;
                break;
        }
    }

    while (isdigit(UCHAR(*pc->p))
        || (base == 16 && isxdigit(UCHAR(*pc->p)))
        || (base == 8 && *pc->p >= '0' && *pc->p <= '7')
        || (base == 2 && (*pc->p == '0' || *pc->p == '1'))
        || (allowdot && *pc->p == '.')
        ) {
        if (*pc->p == '.') {
            allowdot = 0;
            pc->tt = JIM_TT_EXPR_DOUBLE;
        }
        pc->p++;
        pc->len--;
        if (base == 10 && (*pc->p == 'e' || *pc->p == 'E') && (pc->p[1] == '-' || pc->p[1] == '+'
                || isdigit(UCHAR(pc->p[1])))) {
            pc->p += 2;
            pc->len -= 2;
            pc->tt = JIM_TT_EXPR_DOUBLE;
        }
    }
    pc->tend = pc->p - 1;
    return JIM_OK;
}
