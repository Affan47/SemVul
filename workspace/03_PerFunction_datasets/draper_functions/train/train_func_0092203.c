parse_htpl_fetch___fwd(stack, untag)
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
    if (numtokens < 1) RETURN(croak("%sFETCH called with %d arguments, minimum needed is 1", (untag ? "/" : ""), numtokens))
    if (numtokens > 1) RETURN(croak("%sFETCH called with %d arguments, maximum needed is 1", (untag ? "/" : ""), numtokens))
    pushscope(scope_fetch, 0);
    printfcode("${\"%s\"}->rewind if (${\"%s\"});\n", gettoken(1), gettoken(1));
    printfcode("while (${\"%s\"} && !${\"%s\"}->eof && ${\"%s\"}->fetch) {\n", gettoken(1), gettoken(1), gettoken(1));
    nesting = 0;
    RETURN(1)
}
