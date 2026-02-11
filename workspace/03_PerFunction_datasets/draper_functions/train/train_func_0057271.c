make_filter_cmd(cmd, itmp, otmp)
    char_u	*cmd;
    char_u	*itmp;
    char_u	*otmp;
{
    char_u	*buf;
    long_u	len;

    len = (long_u)STRLEN(cmd) + 3;
    if (itmp != NULL)
	len += (long_u)STRLEN(itmp) + 9;
    if (otmp != NULL)
	len += (long_u)STRLEN(otmp) + (long_u)STRLEN(p_srr) + 2;
    buf = lalloc(len, TRUE);
    if (buf == NULL)
	return NULL;

#if (defined(UNIX) && !defined(ARCHIE)) || defined(OS2)


    if (itmp != NULL || otmp != NULL)
	sprintf((char *)buf, "(%s)", (char *)cmd);
    else
	STRCPY(buf, cmd);
    if (itmp != NULL)
    {
	STRCAT(buf, " < ");
	STRCAT(buf, itmp);
    }
#else


    STRCPY(buf, cmd);
    if (itmp != NULL)
    {
	char_u	*p;


	if (*p_shq == NUL)
	{
	    p = vim_strchr(buf, '|');
	    if (p != NULL)
		*p = NUL;
	}
# ifdef RISCOS
	STRCAT(buf, " { < ");
	STRCAT(buf, itmp);
	STRCAT(buf, " } ");
# else
	STRCAT(buf, " <");
	STRCAT(buf, itmp);
# endif
	if (*p_shq == NUL)
	{
	    p = vim_strchr(cmd, '|');
	    if (p != NULL)
	    {
		STRCAT(buf, " ");
		STRCAT(buf, p);
	    }
	}
    }
#endif
    if (otmp != NULL)
	append_redir(buf, p_srr, otmp);

    return buf;
}
