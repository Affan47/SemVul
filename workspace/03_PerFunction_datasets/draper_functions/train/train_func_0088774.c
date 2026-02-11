Scm_List(ScmObj elt, ...)
{
    va_list pvar;
    ScmObj cdr;

    if (elt == NULL) return SCM_NIL;

    va_start(pvar, elt);
    cdr = Scm_VaList(pvar);
    va_end(pvar);
    return Scm_Cons(elt, cdr);
}
