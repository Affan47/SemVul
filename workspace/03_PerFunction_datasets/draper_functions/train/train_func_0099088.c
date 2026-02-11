parse_htpl_define___fwd(stack, untag)
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
    if (numtokens < 1) RETURN(croak("%sDEFINE called with %d arguments, minimum needed is 1", (untag ? "/" : ""), numtokens))
    if (numtokens > 1) RETURN(croak("%sDEFINE called with %d arguments, maximum needed is 1", (untag ? "/" : ""), numtokens))
    pushscope(scope_define, 0);
    setvar("var", (STR)mysprintf("%s", gettoken(1)));
    printcode("&begintransaction;\n");
    nesting = 0;
    RETURN(1)
}
