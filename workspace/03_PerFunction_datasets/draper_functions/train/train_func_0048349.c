nv_esc(cap)
    cmdarg_T	*cap;
{
    int		no_reason;

    no_reason = (cap->oap->op_type == OP_NOP
		&& cap->opcount == 0
		&& cap->count0 == 0
		&& cap->oap->regname == 0
		&& !p_im);

    if (cap->arg)
    {
	if (restart_edit == 0
#ifdef FEAT_CMDWIN
		&& cmdwin_type == 0
#endif
#ifdef FEAT_VISUAL
		&& !VIsual_active
#endif
		&& no_reason)
	    MSG(_("Type  :quit<Enter>  to exit Vim"));


	if (!p_im)
	    restart_edit = 0;
#ifdef FEAT_CMDWIN
	if (cmdwin_type != 0)
	{
	    cmdwin_result = K_IGNORE;
	    got_int = FALSE;
	    return;
	}
#endif
    }

#ifdef FEAT_VISUAL
    if (VIsual_active)
    {
	end_visual_mode();
	check_cursor_col();
	curwin->w_set_curswant = TRUE;
	redraw_curbuf_later(INVERTED);
    }
    else
#endif
	if (no_reason)
	    vim_beep();
    clearop(cap->oap);


    if (restart_edit == 0 && goto_im()
#ifdef FEAT_EX_EXTRA
	    && ex_normal_busy == 0
#endif
	    )
	restart_edit = 'a';
}
