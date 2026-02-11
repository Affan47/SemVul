Scm_RegMatchEnd(ScmRegMatch *rm, ScmObj obj)
{
    struct ScmRegMatchSub *sub = regmatch_ref(rm, obj);
    if (sub == NULL) return SCM_FALSE;
    if (sub->after < 0) regmatch_count_after(rm, sub);
    return Scm_MakeInteger(rm->inputLen - sub->after);
}
