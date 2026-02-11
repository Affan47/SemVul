qf_get_fnum(directory, fname)
    char_u   *directory;
    char_u   *fname;
{
    if (fname == NULL || *fname == NUL)
	return 0;
    {
	char_u	    *ptr;
	int	    fnum;

#ifdef VMS
	vms_remove_version(fname);
#endif
#ifdef BACKSLASH_IN_FILENAME
	if (directory != NULL)
	    slash_adjust(directory);
	slash_adjust(fname);
#endif
	if (directory != NULL && !vim_isAbsName(fname)
		&& (ptr = concat_fnames(directory, fname, TRUE)) != NULL)
	{


	    if (mch_getperm(ptr) < 0)
	    {
		vim_free(ptr);
		directory = qf_guess_filepath(fname);
		if (directory)
		    ptr = concat_fnames(directory, fname, TRUE);
		else
		    ptr = vim_strsave(fname);
	    }

	    fnum = buflist_add(ptr, 0);
	    vim_free(ptr);
	    return fnum;
	}
	return buflist_add(fname, 0);
    }
}
