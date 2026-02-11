install_keyword_root(char *string, int (*handler) (vector))
{
	int r = keyword_alloc(keywords, string, handler, NULL);
	if (!r)
		*keywords_addr = keywords;
	return r;
}
