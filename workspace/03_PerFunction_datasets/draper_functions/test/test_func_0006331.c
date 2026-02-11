leave_tabpage(new_curbuf)
    buf_T	*new_curbuf UNUSED;

{
    tabpage_T	*tp = curtab;

#ifdef FEAT_VISUAL
    reset_VIsual_and_resel();
#endif
#ifdef FEAT_AUTOCMD
    if (new_curbuf != curbuf)
    {
	apply_autocmds(EVENT_BUFLEAVE, NULL, NULL, FALSE, curbuf);
	if (curtab != tp)
	    return FAIL;
    }
    apply_autocmds(EVENT_WINLEAVE, NULL, NULL, FALSE, curbuf);
    if (curtab != tp)
	return FAIL;
    apply_autocmds(EVENT_TABLEAVE, NULL, NULL, FALSE, curbuf);
    if (curtab != tp)
	return FAIL;
#endif
#if defined(FEAT_GUI)

    if (gui.in_use)
	gui_remove_scrollbars();
#endif
    tp->tp_curwin = curwin;
    tp->tp_prevwin = prevwin;
    tp->tp_firstwin = firstwin;
    tp->tp_lastwin = lastwin;
    tp->tp_old_Rows = Rows;
    tp->tp_old_Columns = Columns;
    firstwin = NULL;
    lastwin = NULL;
    return OK;
}
