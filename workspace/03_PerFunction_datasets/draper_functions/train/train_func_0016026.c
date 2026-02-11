parse_htpl_text_read(stack, untag)
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
    if (numtokens < 2) RETURN(croak("%sTEXT READ called with %d arguments, minimum needed is 2", (untag ? "/" : ""), numtokens))
    if (numtokens > 2) RETURN(croak("%sTEXT READ called with %d arguments, maximum needed is 2", (untag ? "/" : ""), numtokens))
    printfcode("${\"%s\"} = &readfile(\"%s\");\n", gettoken(1), gettoken(2));
    nesting = 0;
    RETURN(1)
}
