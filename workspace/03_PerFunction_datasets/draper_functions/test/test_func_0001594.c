getaltfname(errmsg)
    int		errmsg;
{
    char_u	*fname;
    linenr_T	dummy;

    if (buflist_name_nr(0, &fname, &dummy) == FAIL)
    {
	if (errmsg)
	    EMSG(_(e_noalt));
	return NULL;
    }
    return fname;
}
