do_sub_msg(count_only)
    int	    count_only;
{
    int	    len = 0;


    if (((sub_nsubs > p_report && (KeyTyped || sub_nlines > 1 || p_report < 1))
		|| count_only)
	    && messaging())
    {
	if (got_int)
	{
	    STRCPY(msg_buf, _("(Interrupted) "));
	    len = (int)STRLEN(msg_buf);
	}
	if (sub_nsubs == 1)
	    vim_snprintf((char *)msg_buf + len, sizeof(msg_buf) - len,
		    "%s", count_only ? _("1 match") : _("1 substitution"));
	else
	    vim_snprintf((char *)msg_buf + len, sizeof(msg_buf) - len,
		    count_only ? _("%ld matches") : _("%ld substitutions"),
								   sub_nsubs);
	len = (int)STRLEN(msg_buf);
	if (sub_nlines == 1)
	    vim_snprintf((char *)msg_buf + len, sizeof(msg_buf) - len,
		    "%s", _(" on 1 line"));
	else
	    vim_snprintf((char *)msg_buf + len, sizeof(msg_buf) - len,
		    _(" on %ld lines"), (long)sub_nlines);
	if (msg(msg_buf))

	    set_keep_msg(msg_buf, 0);
	return TRUE;
    }
    if (got_int)
    {
	EMSG(_(e_interr));
	return TRUE;
    }
    return FALSE;
}
