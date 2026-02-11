parse_htpl_load(stack, untag)
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
    if (numtokens < 1) RETURN(croak("%sLOAD called with %d arguments, minimum needed is 1", (untag ? "/" : ""), numtokens))
    printfcode("die \"Unknown query\" unless $HTML::HTPL::Sys::query_pool{\"%s\"};\n", gettoken(1));
    printfcode("${\"%s\"} = $HTML::HTPL::Sys::query_pool{\"%s\"}->load(%s);\n", gettoken(1), gettoken(1), numtokens >= abs(2) ? gettokenlist(2, ", ", "", "\"$s\"") : "()");
    nesting = 0;
    RETURN(1)
}
