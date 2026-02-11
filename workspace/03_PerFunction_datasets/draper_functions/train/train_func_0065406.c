expand_wildcards(num_pat, pat, num_file, file, flags)
    int		   num_pat;
    char_u	 **pat;
    int		  *num_file;
    char_u	***file;
    int		   flags;
{
    int		retval;
    int		i, j;
    char_u	*p;
    int		non_suf_match;

    retval = gen_expand_wildcards(num_pat, pat, num_file, file, flags);


    if ((flags & EW_KEEPALL) || retval == FAIL)
	return retval;

#ifdef FEAT_WILDIGN


    if (*p_wig)
    {
	char_u	*ffname;


	for (i = 0; i < *num_file; ++i)
	{
	    ffname = FullName_save((*file)[i], FALSE);
	    if (ffname == NULL)
		break;
# ifdef VMS
	    vms_remove_version(ffname);
# endif
	    if (match_file_list(p_wig, (*file)[i], ffname))
	    {

		vim_free((*file)[i]);
		for (j = i; j + 1 < *num_file; ++j)
		    (*file)[j] = (*file)[j + 1];
		--*num_file;
		--i;
	    }
	    vim_free(ffname);
	}
    }
#endif


    if (*num_file > 1)
    {
	non_suf_match = 0;
	for (i = 0; i < *num_file; ++i)
	{
	    if (!match_suffix((*file)[i]))
	    {


		p = (*file)[i];
		for (j = i; j > non_suf_match; --j)
		    (*file)[j] = (*file)[j - 1];
		(*file)[non_suf_match++] = p;
	    }
	}
    }

    return retval;
}
