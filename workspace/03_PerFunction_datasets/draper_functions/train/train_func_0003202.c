crossref(char *srcfile)
{
    unsigned int i;
    unsigned int length;
    unsigned int entry_no;
    int token;
    struct stat st;

    if (! ((stat(srcfile, &st) == 0)
	   && S_ISREG(st.st_mode))) {
	cannotopen(srcfile);
	errorsfound = YES;
	return;
    }

    entry_no = 0;

    if ((yyin = myfopen(srcfile, "r")) == NULL) {
	cannotopen(srcfile);
	errorsfound = YES;
	return;
    }
    filename = srcfile;
    putfilename(srcfile);
    dbputc('\n');
    dbputc('\n');


    initscanner(srcfile);
    fcnoffset = macrooffset = 0;
    symbols = 0;
    if (symbol == NULL) {
	symbol = mymalloc(msymbols * sizeof(struct symbol));
    }
    for (;;) {


	switch (token = yylex()) {
	default:

	    length = last - first;
	    if (trun_syms == YES && length > 8 &&
		token != INCLUDE && token != NEWFILE) {
		length = 8;
		last = first + 8;
	    }

	    if (length == 0) {
		savesymbol(token, entry_no);
		break;
	    }

	    if (token == FCNDEF) {
		entry_no++;
	    }

	    for (i = 0; i < symbols; ++i) {
		if (length == symbol[i].length
		    && strncmp(my_yytext + first,
			       my_yytext + symbol[i].first,
			       length) == 0
		    && entry_no == symbol[i].fcn_level
		    && token == symbol[i].type
		    ) {
		    break;
		}
	    }
	    if (i == symbols) {
		savesymbol(token, entry_no);
	    }
	    break;

	case NEWLINE:
	    entry_no = 0;
#ifdef USING_LEX
	    --yyleng;
#endif
	    putcrossref();
	    lineno = myylineno;
#ifndef USING_LEX

	    if (my_yytext)
		*my_yytext = '\0';
	    my_yyleng = 0;
#endif
	    break;

	case LEXEOF:


	    if (symbols > 0) {
		putcrossref();
	    }
	    (void) fclose(yyin);


	    dbputc('\t');
	    return;
	}
    }
}
