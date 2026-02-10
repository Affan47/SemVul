parse_htpl_switch_rnd___fwd(stack, untag)
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
    pushscope(scope_random_switch, 0);
    printcode("{\n");
    code = 1;
    kludge_reunifying = 1;
    asprintf(&buff, "SWITCH CASE");
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
