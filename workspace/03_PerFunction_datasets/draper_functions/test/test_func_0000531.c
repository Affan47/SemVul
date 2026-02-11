Scm_BignumToString(ScmBignum *b, int radix, int use_upper)
{
    static const char ltab[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    static const char utab[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *tab = use_upper? utab : ltab;
    ScmObj h = SCM_NIL, t = SCM_NIL;
    ScmBignum *q;
    long rem;
    if (radix < 2 || radix > 36)
        Scm_Error("radix out of range: %d", radix);
    q = SCM_BIGNUM(Scm_BignumCopy(b));
    for (;q->size > 0;) {
        rem = bignum_sdiv(q, radix);
        SCM_ASSERT(rem >= 0 && rem < radix);
        SCM_APPEND1(h, t, SCM_MAKE_CHAR(tab[rem]));
        for (; q->values[q->size-1] == 0 && q->size > 0; q->size--)
            ;
    }
    if (q->sign < 0) SCM_APPEND1(h, t, SCM_MAKE_CHAR('-'));
    return Scm_ListToString(Scm_ReverseX(h));
}
