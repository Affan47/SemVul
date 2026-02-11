Scm_MakeBignumFromSI(long val)
{
    ScmBignum *b;
    if (val == LONG_MIN) {
        b = make_bignum(1);
        b->sign = -1;
        b->values[0] = (unsigned long)LONG_MAX+1;
    } else if (val < 0) {
        b = make_bignum(1);
        b->sign = -1;
        b->values[0] = -val;
    } else {
        b = make_bignum(1);
        b->sign = 1;
        b->values[0] = val;
    }
    return SCM_OBJ(b);
}
