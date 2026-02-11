do_wqall(eap)
    exarg_T	*eap;
{
    buf_T	*buf;
    int		error = 0;
    int		save_forceit = eap->forceit;

    if (eap->cmdidx == CMD_xall || eap->cmdidx == CMD_wqall)
	exiting = TRUE;

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
    {
	if (bufIsChanged(buf))
	{


	    if (not_writing())
	    {
		++error;
		break;
	    }
#ifdef FEAT_BROWSE

	    if (buf->b_ffname == NULL && cmdmod.browse)
		browse_save_fname(buf);
#endif
	    if (buf->b_ffname == NULL)
	    {
		EMSGN(_("E141: No file name for buffer %ld"), (long)buf->b_fnum);
		++error;
	    }
	    else if (check_readonly(&eap->forceit, buf)
		    || check_overwrite(eap, buf, buf->b_fname, buf->b_ffname,
							       FALSE) == FAIL)
	    {
		++error;
	    }
	    else
	    {
		if (buf_write_all(buf, eap->forceit) == FAIL)
		    ++error;
#ifdef FEAT_AUTOCMD

		if (!buf_valid(buf))
		    buf = firstbuf;
#endif
	    }
	    eap->forceit = save_forceit;
	}
    }
    if (exiting)
    {
	if (!error)
	    getout(0);
	not_exiting();
    }
}
