parse_htpl_auth_ifauthorized___rev(stack, untag)
    int untag;
    STR stack; {

    TOKEN token;
    static done = 0;
    STR buff;
    int code;
    static int nesting = 0;
    static int refcount = 0;

    refcount++;
    makepersist(stack);
    nesting++;
    if (nesting > 1) RETURN(croak("Infinite loop in AUTH IFAUTHORIZED"))
    kludge_reunifying = 1;
    asprintf(&buff, "ENDIF");
    kludge_reunifying = 0;
    nest++;
    code = parse_htpl(buff, untag);
    nest--;
    if (!code) {
        croak("Unification of '%s' failed", buff);
        free(buff);
        RETURN(0)
    }
    free(buff);

    nesting = 0;
    RETURN(1)
}
