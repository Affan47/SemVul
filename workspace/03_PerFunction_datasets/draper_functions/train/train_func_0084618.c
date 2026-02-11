re_restrict_alphabet(struct re *re, uchar from, uchar to) {
    int r1, r2;
    int result = 0;

    switch(re->type) {
    case UNION:
    case CONCAT:
        r1 = re_restrict_alphabet(re->exp1, from, to);
        r2 = re_restrict_alphabet(re->exp2, from, to);
        result = (r1 != 0) ? r1 : r2;
        break;
    case CSET:
        if (re->negate) {
            re->negate = 0;
            bitset_negate(re->cset, UCHAR_NUM);
        }
        for (int i=from; i <= to; i++)
            bitset_clr(re->cset, i);
        break;
    case CHAR:
        if (from <= re->c && re->c <= to)
            result = -1;
        break;
    case ITER:
        result = re_restrict_alphabet(re->exp, from, to);
        break;
    case EPSILON:
        break;
    default:
        assert(0);
        abort();
        break;
    }
    return result;
}
