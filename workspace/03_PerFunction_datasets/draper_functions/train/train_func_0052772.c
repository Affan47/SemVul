rc_register_charset(regcomp_ctx *ctx, ScmCharSet *cs)
{
    if (SCM_FALSEP(Scm_Memq(SCM_OBJ(cs), ctx->sets))) {
        ctx->sets = Scm_Cons(SCM_OBJ(cs), ctx->sets);
    }
}
