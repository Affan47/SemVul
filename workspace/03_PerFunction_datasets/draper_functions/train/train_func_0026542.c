rc1_read_integer(regcomp_ctx *ctx)
{
    ScmObj r;
    ScmDString ds;
    ScmChar ch = Scm_GetcUnsafe(ctx->ipat);
    if (!isdigit(ch)) {
        Scm_Error("number expected, but got '%c'", ch);
    }
    Scm_DStringInit(&ds);
    do {
        Scm_DStringPutc(&ds, ch);
        ch = Scm_GetcUnsafe(ctx->ipat);
    } while (ch != SCM_CHAR_INVALID && isdigit(ch));
    if (ch != SCM_CHAR_INVALID) {
        Scm_UngetcUnsafe(ch, ctx->ipat);
    }
    r = Scm_StringToNumber(SCM_STRING(Scm_DStringGet(&ds, 0)),
                           10, FALSE);
    if (SCM_BIGNUMP(r)) {
        Scm_Error("number too big: %S", r);
    }
    SCM_ASSERT(SCM_INTP(r));
    return r;
}
