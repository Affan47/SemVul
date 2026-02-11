ins_compl_add(str, len, icase, fname, cptext, cdir, flags, adup)
    char_u	*str;
    int		len;
    int		icase;
    char_u	*fname;
    char_u	**cptext;
    int		cdir;
    int		flags;
    int		adup;
{
    compl_T	*match;
    int		dir = (cdir == 0 ? compl_direction : cdir);

    ui_breakcheck();
    if (got_int)
	return FAIL;
    if (len < 0)
	len = (int)STRLEN(str);


    if (compl_first_match != NULL && !adup)
    {
	match = compl_first_match;
	do
	{
	    if (    !(match->cp_flags & ORIGINAL_TEXT)
		    && STRNCMP(match->cp_str, str, len) == 0
		    && match->cp_str[len] == NUL)
		return NOTDONE;
	    match = match->cp_next;
	} while (match != NULL && match != compl_first_match);
    }


    ins_compl_del_pum();


    match = (compl_T *)alloc_clear((unsigned)sizeof(compl_T));
    if (match == NULL)
	return FAIL;
    match->cp_number = -1;
    if (flags & ORIGINAL_TEXT)
	match->cp_number = 0;
    if ((match->cp_str = vim_strnsave(str, len)) == NULL)
    {
	vim_free(match);
	return FAIL;
    }
    match->cp_icase = icase;


    if (fname != NULL
	    && compl_curr_match != NULL
	    && compl_curr_match->cp_fname != NULL
	    && STRCMP(fname, compl_curr_match->cp_fname) == 0)
	match->cp_fname = compl_curr_match->cp_fname;
    else if (fname != NULL)
    {
	match->cp_fname = vim_strsave(fname);
	flags |= FREE_FNAME;
    }
    else
	match->cp_fname = NULL;
    match->cp_flags = flags;

    if (cptext != NULL)
    {
	int i;

	for (i = 0; i < CPT_COUNT; ++i)
	    if (cptext[i] != NULL && *cptext[i] != NUL)
		match->cp_text[i] = vim_strsave(cptext[i]);
    }


    if (compl_first_match == NULL)
	match->cp_next = match->cp_prev = NULL;
    else if (dir == FORWARD)
    {
	match->cp_next = compl_curr_match->cp_next;
	match->cp_prev = compl_curr_match;
    }
    else
    {
	match->cp_next = compl_curr_match;
	match->cp_prev = compl_curr_match->cp_prev;
    }
    if (match->cp_next)
	match->cp_next->cp_prev = match;
    if (match->cp_prev)
	match->cp_prev->cp_next = match;
    else
	compl_first_match = match;
    compl_curr_match = match;


    if (compl_get_longest && (flags & ORIGINAL_TEXT) == 0)
	ins_compl_longest_match(match);

    return OK;
}
