P_Begin1 (Object forms) {
    register int n;
    Object r, ret;
    GC_Node;
    TC_Prolog;

    if (Nullp (forms))
        return Unspecified;
    GC_Link (forms);
    TC_Disable;
    for (n = 1; !Nullp (Cdr (forms)); n = 0, forms = Cdr (forms)) {
        r = Eval (Car (forms));
        if (n)
            ret = r;
    }
    GC_Unlink;
    TC_Enable;
    r = Eval (Car (forms));
    return n ? r : ret;
}
