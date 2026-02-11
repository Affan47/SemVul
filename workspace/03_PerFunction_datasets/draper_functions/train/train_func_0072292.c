Scm_Reverse2(ScmObj list, ScmObj tail)
{
    ScmObj cp, result;
    ScmPair *p;

    if (!SCM_PAIRP(list)) return tail;

    p = SCM_NEW(ScmPair);
    SCM_SET_CAR(p, SCM_NIL);
    SCM_SET_CDR(p, tail);
    result = SCM_OBJ(p);
    SCM_FOR_EACH(cp, list) {
	SCM_SET_CAR(result, SCM_CAR(cp));
        p = SCM_NEW(ScmPair);
        SCM_SET_CAR(p, SCM_NIL);
        SCM_SET_CDR(p, result);
        result = SCM_OBJ(p);
    }
    return SCM_CDR(result);
}
