Scm_SortArray(ScmObj *elts, int nelts, ScmObj cmpfn)
{
    int limit, i;
    if (nelts <= 1) return;

    for (i=nelts,limit=1; i > 0; limit++) {i>>=1;}
    if (SCM_PROCEDUREP(cmpfn)) {
        sort_q(elts, 0, nelts-1, 0, limit, cmp_scm, cmpfn);
    } else {
        sort_q(elts, 0, nelts-1, 0, limit, cmp_int, NULL);
    }
}
