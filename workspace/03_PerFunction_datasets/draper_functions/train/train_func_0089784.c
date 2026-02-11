buflist_findname_exp(fname)
    char_u *fname;
{
    char_u	*ffname;
    buf_T	*buf = NULL;


    ffname = FullName_save(fname,
#ifdef UNIX
	    TRUE
#else
	    FALSE
#endif
	    );
    if (ffname != NULL)
    {
	buf = buflist_findname(ffname);
	vim_free(ffname);
    }
    return buf;
}
