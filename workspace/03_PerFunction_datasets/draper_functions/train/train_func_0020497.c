Scm_AssocDeleteX(ScmObj elt, ScmObj alist, int cmpmode)
{
    ScmObj cp, prev = SCM_NIL;
    if (!SCM_LISTP(alist)) {
        Scm_Error("assoc-delete!: list required, but got %S", alist);
    }
    SCM_FOR_EACH(cp, alist) {
        ScmObj e = SCM_CAR(cp);
        if (SCM_PAIRP(e)) {
            if (Scm_EqualM(elt, SCM_CAR(e), cmpmode)) {
                if (SCM_NULLP(prev)) {
                    alist = SCM_CDR(cp);
                    continue;
                } else {
                    SCM_SET_CDR(prev, SCM_CDR(cp));
                }
            }
        }
        prev = cp;
    }
    return alist;
}
