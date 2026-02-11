fname_match(prog, name)
    regprog_T	*prog;
    char_u	*name;
{
    char_u	*match = NULL;
    char_u	*p;
    regmatch_T	regmatch;

    if (name != NULL)
    {
	regmatch.regprog = prog;
	regmatch.rm_ic = p_fic;
	if (vim_regexec(&regmatch, name, (colnr_T)0))
	    match = name;
	else
	{

	    p = home_replace_save(NULL, name);
	    if (p != NULL && vim_regexec(&regmatch, p, (colnr_T)0))
		match = name;
	    vim_free(p);
	}
    }

    return match;
}
