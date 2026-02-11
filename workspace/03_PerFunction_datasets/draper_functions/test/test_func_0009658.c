check_re(const gchar *re_src, regex_t **re, gboolean glob, gboolean nocase, const gchar *string)
{
	gchar	*glob_re = NULL;

	if(*re == NULL)
	{
		if(glob)
		{
			glob_re = stu_glob_to_re(re_src);
			re_src = glob_re;
		}
		*re = g_malloc(sizeof **re);
		regcomp(*re, re_src, REG_EXTENDED | REG_NOSUB | (nocase ? REG_ICASE : 0));
		if(glob_re)
			g_free(glob_re);
	}
	if(*re != NULL)
		return regexec(*re, string, 0, NULL, 0) == 0;
	return 0;
}
