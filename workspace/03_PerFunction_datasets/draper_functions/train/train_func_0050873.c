escape_strrchr(const char * haystack, int c, const char *toescape)
{
	char * p;
	if (strchr(toescape,c)==NULL)
		return strrchr(haystack,c);

	if ((p=strrchr(haystack,c))==NULL)
		return NULL;

	if (p==haystack)
		return p;

	if (*(p-1)!=c)
		return p;

	p-=2;

	return escape_strrchr(p,c,toescape);
}
