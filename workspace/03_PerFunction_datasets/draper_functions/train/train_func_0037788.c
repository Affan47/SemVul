parse_htpl_class___fwd(stack, untag)
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
    if (numtokens < 1) RETURN(croak("%sCLASS called with %d arguments, minimum needed is 1", (untag ? "/" : ""), numtokens))
    pushscope(scope_class, 0);
    if (disposetrue((STR)mysprintf("%s", getsubtoken(1, ':', 2))))  {
        printfcode(" package %s;\n", getsubtoken(1, ':', 1));
        printfcode(" @ISA = split(/:/, \"%s\");\n", gettoken(1));
        printcode("	shift @ISA;\n");
        printfcode("        package %s::__shadow__;\n", getsubtoken(1, ':', 1));
        printfcode("        @ISA = map { \"${_}::__shadow__\"; } @%s::ISA;\n", getsubtoken(1, ':', 1));
        printcode("	\n");
        setvar("cls", (STR)mysprintf("%s", getsubtoken(1, ':', 1)));
    }
    if (!(disposetrue((STR)mysprintf("%s", getsubtoken(1, ':', 2)))))  {
        printfcode(" package %s;\n", gettoken(1));
        printcode("	\n");
        setvar("cls", (STR)mysprintf("%s", gettoken(1)));
    }
    printfcode(" use HTML::HTPL::Munge %s;\n", numtokens >= abs(2) ? gettokenlist(2, ", ", "", "\"$s\"") : "()");
    printcode("	\n");
    printcode("	sub set {\n");
    printcode("	my $self = shift;\n");
    printcode("	my %hash = @_;\n");
    printcode("	foreach (keys %hash) {\n");
    printcode("		$self->{$_} = $hash{$_};\n");
    printcode("	}\n");
    printcode("}\n");
    asprintf(&buff, "#CLSUTILS OTHER\n");
    nest++;
    code = parse_htpl(strchr(buff, '#') + 1, 0);
    nest--;
    if (!code) {
        croak("Unification of '%s' failed", buff);
        free(buff);
        RETURN(0)
    }
    free(buff);
    printcode("sub __shadow__clone {\n");
    printcode("	require Clone;\n");
    printcode("	Clone::clone($self);\n");
    printcode("}\n");
    nesting = 0;
    RETURN(1)
}
