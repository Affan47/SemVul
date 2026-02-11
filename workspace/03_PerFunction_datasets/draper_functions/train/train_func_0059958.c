mutt_convert_string(const char *ps, iconv_t cd, int is_utf)
{
#ifdef HAVE_ICONV
	char *repls[] = { "\357\277\275", "?", 0 };

	char *ib;
	char *buf, *ob;
	size_t ibl, obl;
	char **inrepls = 0;
	char *outrepl = 0;

	if ( is_utf == 2 )
		outrepl = repls[0];
	else if ( is_utf == 1 )
		inrepls = repls;
	else
		outrepl = "?";

	ib = (char *) ps;
	ibl = strlen(ps) + 1;
	obl = 16 * ibl;
	ob = buf = xmalloc (obl + 1);

	mutt_iconv (cd, &ib, &ibl, &ob, &obl, inrepls, outrepl);

	*ob = '\0';

	buf = (char*)xrealloc((void*)buf, strlen(buf)+1);
	return buf;

#else
	return NULL;
#endif
}
