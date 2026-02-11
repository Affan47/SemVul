Scm_BignumCopy(ScmBignum *b)
{
    u_int i;
    ScmBignum *c = make_bignum(b->size);
    c->sign = b->sign;
    for (i=0; i<b->size; i++) c->values[i] = b->values[i];
    return SCM_OBJ(c);
}
