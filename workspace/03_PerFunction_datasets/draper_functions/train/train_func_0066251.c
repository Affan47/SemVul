yylex ()
    {
    int			backslashed;
    register int	ch;
    register unsigned char *
			lexp;
    unsigned char	lexstring[256];

    while ((ch = grabchar ()) != EOF  &&  (isspace (ch)  ||  ch == '#'))
	{
	if (ch == '#')
	    {
	    while ((ch = grabchar ()) != EOF  &&  ch != '\n')
		;
	    }
	}
    switch (ch)
	{
	case EOF:
	    return EOF;
	case '"':
	    getqstring ();
	    return STRING;
	case '-':
	case '>':
	case ',':
	case ':':
	case '.':
	case '*':
	case '~':
	    yylval.simple = ch;
	    return ch;
	case '[':
	    getrange ();
	    return RANGE;
	}


    backslashed = 0;
    lexp = lexstring;
    for (  ;  ;  )
	{
	switch (ch)
	    {
	    case EOF:
		*lexp = '\0';
		return kwanalyze (backslashed, lexstring);
	    case '\\':
		backslashed = 1;
		ch = backch ();
		*lexp++ = (unsigned char) ch;
		break;
	    case ' ':
	    case '\t':
	    case '\n':
	    case '\f':
	    case '\r':
		*lexp = '\0';
		return kwanalyze (backslashed, lexstring);
	    case '#':
	    case '>':
	    case ':':
	    case '-':
	    case ',':
	    case '[':
		ungrabchar (ch);
		*lexp = '\0';
		return kwanalyze (backslashed, lexstring);
	    default:
		*lexp++ = (unsigned char) ch;
		break;
	    }
	ch = grabchar ();
	}
    }
