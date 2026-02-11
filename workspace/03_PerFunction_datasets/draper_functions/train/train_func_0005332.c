TeX_math_begin (bufp)
    unsigned char **	bufp;
    {
    int			didskip = 0;

    if (**bufp == TEXDOLLAR)
	{
	if ((*bufp)[1] == TEXDOLLAR)
	    (*bufp)++;
	return 1;
	}
    while (**bufp == TEXBACKSLASH)
	{
	didskip = 1;
	(*bufp)++;
	if (**bufp == TEXLEFTPAREN  ||  **bufp == TEXLEFTSQUARE)
	    return 1;
	else if (!isalpha(**bufp)  &&  **bufp != '@')
	    return 0;
	else if (TeX_strncmp (*bufp, "begin", 5) == 0)
	    {
	    if (TeX_math_check ('b', bufp))
		return 1;
	    else
		(*bufp)--;
	    }
	else
	    {
	    TeX_skip_check (bufp);
	    return 0;
	    }
	}


    if ((**bufp == TEXLEFTSQUARE  ||  **bufp == TEXLEFTANGLE)
      &&  (*bufp)[1] == TEXDOT)
	{
	(*bufp)++;
	while (**bufp)
	    {
	    if (*(*bufp)++ == TEXDOT
	      &&  (**bufp == TEXRIGHTSQUARE  ||  **bufp == TEXRIGHTANGLE))
		return TeX_math_begin (bufp);
	    }
	return 0;
	}
    else if (didskip)
	{


	(*bufp)--;
	}
    return 0;
    }
