main (int argc, char **argv)
{
    if (argc != 3)
    {
        copyright("Make Optimizing Compiler", version, release);
        error("Usage: %s source dest\n"
              "where:\n"
              "\tsource: source file to compile\n"
              "\t        (normally output from ICM-PP)\n"
              "\tdest:   name of binary file to generate\n"
              ,
              program_name(argv[0]));
    }

    if
    (
        !(yyin = fopen(argv[1], "rt"))
        ||
        !(s_bin = fopen(argv[2], "w+b"))
    )
        error("%s Can't read/write file(s)");


    dead = xrealloc(NULL, sizeof(unsigned));
    dead[0] = 0;

    stringbuf = xstrdup(nullstring);
    lexstring = xstrdup(nullstring);


    fseek(s_bin, sizeof(BIN_HEADER_), SEEK_SET);

    #ifdef YYDEBUG
        yydebug = YYDEBUG;
    #endif

    yyparse();

    if (!yynerrs)
        backend();
    else
        printf("\n%u error(s) detected\n", (unsigned)errcount);

    return(yynerrs != 0);
}
