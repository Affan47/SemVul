put_escstr(fd, strstart, what)
    FILE	*fd;
    char_u	*strstart;
    int		what;
{
    char_u	*str = strstart;
    int		c;
    int		modifiers;


    if (*str == NUL && what == 1)
    {
	if (fprintf(fd, "<Nop>") < 0)
	    return FAIL;
	return OK;
    }

    for ( ; *str != NUL; ++str)
    {
#ifdef FEAT_MBYTE
	char_u	*p;


	p = mb_unescape(&str);
	if (p != NULL)
	{
	    while (*p != NUL)
		if (fputc(*p++, fd) < 0)
		    return FAIL;
	    --str;
	    continue;
	}
#endif

	c = *str;


	if (c == K_SPECIAL && what != 2)
	{
	    modifiers = 0x0;
	    if (str[1] == KS_MODIFIER)
	    {
		modifiers = str[2];
		str += 3;
		c = *str;
	    }
	    if (c == K_SPECIAL)
	    {
		c = TO_SPECIAL(str[1], str[2]);
		str += 2;
	    }
	    if (IS_SPECIAL(c) || modifiers)
	    {
		if (fprintf(fd, "%s", (char *)get_special_key_name(c, modifiers)) < 0)
		    return FAIL;
		continue;
	    }
	}


	if (c == NL)
	{
	    if (what == 2)
	    {
		if (fprintf(fd, IF_EB("\\\026\n", "\\" CTRL_V_STR "\n")) < 0)
		    return FAIL;
	    }
	    else
	    {
		if (fprintf(fd, "<NL>") < 0)
		    return FAIL;
	    }
	    continue;
	}


	if (what == 2 && (vim_iswhite(c) || c == '"' || c == '\\'))
	{
	    if (putc('\\', fd) < 0)
		return FAIL;
	}
	else if (c < ' ' || c > '~' || c == '|'
		|| (what == 0 && c == ' ')
		|| (what == 1 && str == strstart && c == ' ')
		|| (what != 2 && c == '<'))
	{
	    if (putc(Ctrl_V, fd) < 0)
		return FAIL;
	}
	if (putc(c, fd) < 0)
	    return FAIL;
    }
    return OK;
}
