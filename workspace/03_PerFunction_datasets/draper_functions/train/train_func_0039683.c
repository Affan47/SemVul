rc1_group_name(regcomp_ctx *ctx)
{
    ScmChar ch;
    ScmDString ds;
    Scm_DStringInit(&ds);

    for (;;) {
        ch = Scm_GetcUnsafe(ctx->ipat);
        if (ch == SCM_CHAR_INVALID) return SCM_FALSE;
        if (ch == '>') {
            return Scm_Intern(SCM_STRING(Scm_DStringGet(&ds, 0)));
        }
        if (ch == '\\') {
            ch = Scm_GetcUnsafe(ctx->ipat);
            if (ch == SCM_CHAR_INVALID) return SCM_FALSE;

        }
        Scm_DStringPutc(&ds, ch);
    }
    return SCM_UNDEFINED;
}
