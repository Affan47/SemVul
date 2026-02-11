put_in_typebuf(s, esc, colon, silent)
    char_u	*s;
    int		esc;
    int		colon;
    int		silent;
{
    int		retval = OK;

    put_reedit_in_typebuf(silent);
    if (colon)
	retval = ins_typebuf((char_u *)"\n", REMAP_YES, 0, TRUE, silent);
    if (retval == OK)
    {
	char_u	*p;

	if (esc)
	    p = vim_strsave_escape_csi(s);
	else
	    p = s;
	if (p == NULL)
	    retval = FAIL;
	else
	    retval = ins_typebuf(p, REMAP_YES, 0, TRUE, silent);
	if (esc)
	    vim_free(p);
    }
    if (colon && retval == OK)
	retval = ins_typebuf((char_u *)":", REMAP_YES, 0, TRUE, silent);
    return retval;
}
