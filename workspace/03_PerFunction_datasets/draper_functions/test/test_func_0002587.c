pvar_to_pvref(PatternContext *ctx,
                                   ScmSyntaxPattern *pat,
                                   ScmObj pvar)
{
    ScmObj q = Scm_Assq(pvar, ctx->pvars), pvref;
    if (!SCM_PAIRP(q)) return pvar;
    pvref = SCM_CDR(q);
    if (PVREF_LEVEL(pvref) > pat->level) {
        Scm_Error("%S: Pattern variable %S is used in wrong level: %S",
                  ctx->name, pvar, ctx->form);
    }
    return pvref;
}
