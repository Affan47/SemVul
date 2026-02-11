GetName(F, buff)
    register FILE	*F;
    register char	*buff;
{
    static char		SPOOL[] = _PATH_SPOOL;
    register int	c;
    register char	*p;


    while ((c = getc(F)) == ' ' || c == '<')
	continue;
    if (c == EOF || c == '\n')
	return FALSE;

    (void)strcpy(buff, SPOOL);
    p = &buff[STRLEN(SPOOL)];
    *p++ = '/';
    *p++ = (char)c;
    while ((c = getc(F)) != EOF && c != ' ' && c != '\n')
	*p++ = (char)(c == '.' ? '/' : c);
    *p = '\0';
    return TRUE;
}
