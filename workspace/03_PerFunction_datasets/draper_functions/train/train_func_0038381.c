xfuncall(void)
{
    LVAL *newfp;
    int argc;


    newfp = xlsp;
    pusharg(cvfixnum((FIXTYPE)(newfp - xlfp)));
    pusharg(xlgetarg());
    pusharg(NIL);


    for (argc = 0; moreargs(); ++argc)
        pusharg(nextarg());


    newfp[2] = cvfixnum((FIXTYPE)argc);
    xlfp = newfp;


    return (xlapply(argc));
}
