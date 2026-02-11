change_warning(col)
    int	    col;

{
    static char *w_readonly = N_("W10: Warning: Changing a readonly file");

    if (curbuf->b_did_warn == FALSE
	    && curbufIsChanged() == 0
#ifdef FEAT_AUTOCMD
	    && !autocmd_busy
#endif
	    && curbuf->b_p_ro)
    {
#ifdef FEAT_AUTOCMD
	++curbuf_lock;
	apply_autocmds(EVENT_FILECHANGEDRO, NULL, NULL, FALSE, curbuf);
	--curbuf_lock;
	if (!curbuf->b_p_ro)
	    return;
#endif


	msg_start();
	if (msg_row == Rows - 1)
	    msg_col = col;
	msg_source(hl_attr(HLF_W));
	MSG_PUTS_ATTR(_(w_readonly), hl_attr(HLF_W) | MSG_HIST);
#ifdef FEAT_EVAL
	set_vim_var_string(VV_WARNINGMSG, (char_u *)_(w_readonly), -1);
#endif
	msg_clr_eos();
	(void)msg_end();
	if (msg_silent == 0 && !silent_mode)
	{
	    out_flush();
	    ui_delay(1000L, TRUE);
	}
	curbuf->b_did_warn = TRUE;
	redraw_cmdline = FALSE;
	if (msg_row < Rows - 1)
	    showmode();
    }
}
