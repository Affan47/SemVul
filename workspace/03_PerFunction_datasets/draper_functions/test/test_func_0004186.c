HeaderFind(Article, Header, size)
    char		*Article;
    char		*Header;
    register int	size;
{
    register char	*p;

    for (p = Article; ; ) {


	if (p[size] == ':'
	 && ISWHITE(p[size + 1])
	 && caseEQn(p, Header, (SIZE_T)size)) {
	    for (p += size; *++p != '\n' && ISWHITE(*p); )
		continue;
	    return p;
	}
	if ((p = strchr(p, '\n')) == NULL || *++p == '\n')
	    return NULL;
    }
}
