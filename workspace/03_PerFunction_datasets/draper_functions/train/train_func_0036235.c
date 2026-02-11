makeswapname(buf, second_try)
	BUF		*buf;
	int		second_try;
{
	char_u		*r, *s, *fname;
	char_u		*pdir;

	r = modname(curbuf->b_xfilename, (char_u *)".swp");


	if (*p_dir == NUL || r == NULL || (!second_try && *p_dir != '>'))
		return r;

	fname = gettail(r);
	if (*p_dir == '>')
		pdir = p_dir + 1;
	else
		pdir = p_dir;
	s = alloc((unsigned)(STRLEN(pdir) + STRLEN(fname) + 2));
	if (s != NULL)
	{
		STRCPY(s, pdir);
		if (*s && !ispathsep(*(s + STRLEN(s) - 1)))
			STRCAT(s, PATHSEPSTR);
		STRCAT(s, fname);
	}
	free(r);
	return s;
}
