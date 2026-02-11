parse_htpl_servboxen_decide(stack, untag)
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
    if (numtokens < 2) RETURN(croak("%sSERVBOXEN DECIDE called with %d arguments, minimum needed is 2", (untag ? "/" : ""), numtokens))
    if (numtokens >= 3)  {
        code = 1;
        kludge_reunifying = 1;
        asprintf(&buff, "%s", gettokenlist(2, " ", "", ""));
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
    }
    if (numtokens >= 3)  {
        code = 1;
        kludge_reunifying = 1;
        asprintf(&buff, "SERVBOXEN DOIT %s %s", gettoken(4), gettoken(1));
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
    }
    if (numtokens <= 2)  {
        code = 1;
        kludge_reunifying = 1;
        asprintf(&buff, "SERVBOXEN DOIT %s %s", gettoken(2), gettoken(1));
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
    }
    nesting = 0;
    RETURN(1)
}
