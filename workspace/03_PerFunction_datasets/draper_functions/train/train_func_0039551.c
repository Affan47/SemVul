Scm_DeleteKeywordX(ScmObj key, ScmObj list)
{
    ScmObj cp, prev = SCM_FALSE;
    SCM_FOR_EACH(cp, list) {
        if (!SCM_PAIRP(SCM_CDR(cp))) {
            Scm_Error("incomplete key list: %S", list);
        }
        if (key == SCM_CAR(cp)) {

            if (SCM_FALSEP(prev)) {

                return Scm_DeleteKeywordX(key, SCM_CDR(SCM_CDR(cp)));
            } else {
                ScmObj tail = Scm_DeleteKeywordX(key, SCM_CDR(SCM_CDR(cp)));
                SCM_SET_CDR(prev, tail);
                return list;
            }
        }
        cp = SCM_CDR(cp);
        prev = cp;
    }
    return list;
}
