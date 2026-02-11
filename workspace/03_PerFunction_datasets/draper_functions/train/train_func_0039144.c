dbg_check_breakpoint(eap)
    exarg_T	*eap;
{
    char_u	*p;

    debug_skipped = FALSE;
    if (debug_breakpoint_name != NULL)
    {
	if (!eap->skip)
	{

	    if (debug_breakpoint_name[0] == K_SPECIAL
		    && debug_breakpoint_name[1] == KS_EXTRA
		    && debug_breakpoint_name[2] == (int)KE_SNR)
		p = (char_u *)"<SNR>";
	    else
		p = (char_u *)"";
	    smsg((char_u *)_("Breakpoint in \"%s%s\" line %ld"),
		    p,
		    debug_breakpoint_name + (*p == NUL ? 0 : 3),
		    (long)debug_breakpoint_lnum);
	    debug_breakpoint_name = NULL;
	    do_debug(eap->cmd);
	}
	else
	{
	    debug_skipped = TRUE;
	    debug_skipped_name = debug_breakpoint_name;
	    debug_breakpoint_name = NULL;
	}
    }
    else if (ex_nesting_level <= debug_break_level)
    {
	if (!eap->skip)
	    do_debug(eap->cmd);
	else
	{
	    debug_skipped = TRUE;
	    debug_skipped_name = NULL;
	}
    }
}
