parse_cpp_line(unsigned long lineno)
{
    lineno_ = lineno;
    index_ = 0;
    in_comment_ = FALSE;

    dprintf2(D_CPP|D_VERBOSE, "parse_cpp_line: line[%lu]=\"%s\"\n",
    	     lineno, line_.data());

#if 0
    int c;
    fprintf(stderr, "cpp_parser_t::parse: line[%lu]=\"%s\"\n\t\t\"",
	    lineno, data_);
    while ((c = getc_commentless()) != EOF)
    {
	fputc(c, stderr);
    }
    fprintf(stderr, "\"\n");
#endif

#if 0
    int tok;
    fprintf(stderr, "cpp_parser_t::parse: line[%lu]=\"%s\"\n ->",
	    lineno, data_);
    while ((tok = get_token()) != EOF)
    {
    	fprintf(stderr, " %d(%s)", tok, token_as_string(tok));
    }
    fprintf(stderr, "\n");
#endif

    int tok = get_token();
    switch (tok)
    {
    case T_IF: parse_if(); break;
    case T_IFDEF: parse_ifdef(); break;
    case T_IFNDEF: parse_ifndef(); break;
    case T_ELSE: parse_else(); break;
    case T_ENDIF: parse_endif(); break;
    }

    post_line();
}
