ex_cbuffer(eap)
    exarg_T   *eap;
{
    buf_T	*buf = NULL;
    qf_info_T	*qi = &ql_info;

    if (eap->cmdidx == CMD_lbuffer || eap->cmdidx == CMD_lgetbuffer
	    || eap->cmdidx == CMD_laddbuffer)
    {
	qi = ll_get_or_alloc_list(curwin);
	if (qi == NULL)
	    return;
    }

    if (*eap->arg == NUL)
	buf = curbuf;
    else if (*skipwhite(skipdigits(eap->arg)) == NUL)
	buf = buflist_findnr(atoi((char *)eap->arg));
    if (buf == NULL)
	EMSG(_(e_invarg));
    else if (buf->b_ml.ml_mfp == NULL)
	EMSG(_("E681: Buffer is not loaded"));
    else
    {
	if (eap->addr_count == 0)
	{
	    eap->line1 = 1;
	    eap->line2 = buf->b_ml.ml_line_count;
	}
	if (eap->line1 < 1 || eap->line1 > buf->b_ml.ml_line_count
		|| eap->line2 < 1 || eap->line2 > buf->b_ml.ml_line_count)
	    EMSG(_(e_invrange));
	else
	{
	    char_u *qf_title = *eap->cmdlinep;

	    if (buf->b_sfname)
	    {
		vim_snprintf((char *)IObuff, IOSIZE, "%s (%s)",
				     (char *)qf_title, (char *)buf->b_sfname);
		qf_title = IObuff;
	    }

	    if (qf_init_ext(qi, NULL, buf, NULL, p_efm,
			    (eap->cmdidx != CMD_caddbuffer
			     && eap->cmdidx != CMD_laddbuffer),
						   eap->line1, eap->line2,
						   qf_title) > 0
		    && (eap->cmdidx == CMD_cbuffer
			|| eap->cmdidx == CMD_lbuffer))
		qf_jump(qi, 0, 0, eap->forceit);
	}
    }
}
