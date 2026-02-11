start_parse(char* fname) {

    if (GM_start_parse(fname) == 0) {
        printf("Error in loading %s\n", fname);
        return 0;
    }


    return yyparse();
}
