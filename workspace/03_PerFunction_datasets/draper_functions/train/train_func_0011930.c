ex_quit(eap)
    exarg_T	*eap;
{
#ifdef FEAT_CMDWIN
    if (cmdwin_type != 0)
    {
	cmdwin_result = Ctrl_C;
	return;
    }
#endif

    if (text_locked())
    {
	text_locked_msg();
	return;
    }
#ifdef FEAT_AUTOCMD
    apply_autocmds(EVENT_QUITPRE, NULL, NULL, FALSE, curbuf);


    if (curbuf_locked() || (curbuf->b_nwindows == 1 && curbuf->b_closing))
	return;
#endif

#ifdef FEAT_NETBEANS_INTG
    netbeansForcedQuit = eap->forceit;
#endif


    if (check_more(FALSE, eap->forceit) == OK && only_one_window())
	exiting = TRUE;
    if ((!P_HID(curbuf)
		&& check_changed(curbuf, (p_awa ? CCGD_AW : 0)
				       | (eap->forceit ? CCGD_FORCEIT : 0)
				       | CCGD_EXCMD))
	    || check_more(TRUE, eap->forceit) == FAIL
	    || (only_one_window() && check_changed_any(eap->forceit)))
    {
	not_exiting();
    }
    else
    {
#ifdef FEAT_WINDOWS
	if (only_one_window())
#endif
	    getout(0);
#ifdef FEAT_WINDOWS
# ifdef FEAT_GUI
	need_mouse_correct = TRUE;
# endif

	win_close(curwin, !P_HID(curwin->w_buffer) || eap->forceit);
#endif
    }
}
