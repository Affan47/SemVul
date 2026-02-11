Scm_DeleteDuplicates(ScmObj list, int cmpmode)
{
    ScmObj result = SCM_NIL, tail = SCM_NIL, lp;
    SCM_FOR_EACH(lp, list) {
        if (SCM_FALSEP(Scm_Member(SCM_CAR(lp), result, cmpmode))) {
            SCM_APPEND1(result, tail, SCM_CAR(lp));
        }
    }
    if (!SCM_NULLP(lp) && !SCM_NULLP(tail)) SCM_SET_CDR(tail, lp);
    return result;
}
