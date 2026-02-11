Scm_PutBinaryF16(ScmUVector *uv, int off, ScmObj val, ScmSymbol *e)
{
    swap_f16_t v;
    CHECK_ENDIAN(e);
    v.val = Scm_DoubleToHalf(Scm_GetDouble(val));
    SWAP_16(e, v);
    inject(uv, v.buf, off, 2);
}
