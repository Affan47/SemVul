ExpandRTDir(pat, num_file, file, dirnames)
    char_u	*pat;
    int		*num_file;
    char_u	***file;
    char	*dirnames[];
{
    char_u	*matches;
    char_u	*s;
    char_u	*e;
    garray_T	ga;
    int		i;
    int		pat_len;

    *num_file = 0;
    *file = NULL;
    pat_len = (int)STRLEN(pat);
    ga_init2(&ga, (int)sizeof(char *), 10);

    for (i = 0; dirnames[i] != NULL; ++i)
    {
	s = alloc((unsigned)(STRLEN(dirnames[i]) + pat_len + 7));
	if (s == NULL)
	{
	    ga_clear_strings(&ga);
	    return FAIL;
	}
	sprintf((char *)s, "%s/%s*.vim", dirnames[i], pat);
	matches = globpath(p_rtp, s, 0);
	vim_free(s);
	if (matches == NULL)
	    continue;

	for (s = matches; *s != NUL; s = e)
	{
	    e = vim_strchr(s, '\n');
	    if (e == NULL)
		e = s + STRLEN(s);
	    if (ga_grow(&ga, 1) == FAIL)
		break;
	    if (e - 4 > s && STRNICMP(e - 4, ".vim", 4) == 0)
	    {
		for (s = e - 4; s > matches; mb_ptr_back(matches, s))
		    if (*s == '\n' || vim_ispathsep(*s))
			break;
		++s;
		((char_u **)ga.ga_data)[ga.ga_len] =
					    vim_strnsave(s, (int)(e - s - 4));
		++ga.ga_len;
	    }
	    if (*e != NUL)
		++e;
	}
	vim_free(matches);
    }
    if (ga.ga_len == 0)
	return FAIL;


    remove_duplicates(&ga);

    *file = ga.ga_data;
    *num_file = ga.ga_len;
    return OK;
}
