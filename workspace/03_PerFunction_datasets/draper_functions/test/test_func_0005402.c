cin_isfuncdecl(sp, first_lnum, min_lnum, ind_maxparen, ind_maxcomment)
    char_u	**sp;
    linenr_T	first_lnum;
    linenr_T	min_lnum;
    int		ind_maxparen;
    int		ind_maxcomment;
{
    char_u	*s;
    linenr_T	lnum = first_lnum;
    int		retval = FALSE;
    pos_T	*trypos;
    int		just_started = TRUE;

    if (sp == NULL)
	s = ml_get(lnum);
    else
	s = *sp;

    if (find_last_paren(s, '(', ')')
	&& (trypos = find_match_paren(ind_maxparen, ind_maxcomment)) != NULL)
    {
	lnum = trypos->lnum;
	if (lnum < min_lnum)
	    return FALSE;

	s = ml_get(lnum);
    }


    if (cin_ispreproc(s))
	return FALSE;

    while (*s && *s != '(' && *s != ';' && *s != '\'' && *s != '"')
    {
	if (cin_iscomment(s))
	    s = cin_skipcomment(s);
	else
	    ++s;
    }
    if (*s != '(')
	return FALSE;

    while (*s && *s != ';' && *s != '\'' && *s != '"')
    {
	if (*s == ')' && cin_nocode(s + 1))
	{


	    lnum = first_lnum - 1;
	    s = ml_get(lnum);
	    if (*s == NUL || s[STRLEN(s) - 1] != '\\')
		retval = TRUE;
	    goto done;
	}
	if ((*s == ',' && cin_nocode(s + 1)) || s[1] == NUL || cin_nocode(s))
	{
	    int comma = (*s == ',');


	    for (;;)
	    {
		if (lnum >= curbuf->b_ml.ml_line_count)
		    break;
		s = ml_get(++lnum);
		if (!cin_ispreproc(s))
		    break;
	    }
	    if (lnum >= curbuf->b_ml.ml_line_count)
		break;


	    s = skipwhite(s);
	    if (!just_started && (!comma && *s != ',' && *s != ')'))
		break;
	    just_started = FALSE;
	}
	else if (cin_iscomment(s))
	    s = cin_skipcomment(s);
	else
	{
	    ++s;
	    just_started = FALSE;
	}
    }

done:
    if (lnum != first_lnum && sp != NULL)
	*sp = ml_get(first_lnum);

    return retval;
}
