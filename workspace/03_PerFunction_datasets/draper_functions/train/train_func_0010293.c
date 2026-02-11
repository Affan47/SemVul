u_doit(startcount)
    int startcount;
{
    int count = startcount;

    if (!undo_allowed())
	return;

    u_newcount = 0;
    u_oldcount = 0;
    if (curbuf->b_ml.ml_flags & ML_EMPTY)
	u_oldcount = -1;
    while (count--)
    {


	change_warning(0);

	if (undo_undoes)
	{
	    if (curbuf->b_u_curhead == NULL)
		curbuf->b_u_curhead = curbuf->b_u_newhead;
	    else if (p_ul > 0)

		curbuf->b_u_curhead = curbuf->b_u_curhead->uh_next.ptr;

	    if (curbuf->b_u_numhead == 0 || curbuf->b_u_curhead == NULL)
	    {

		curbuf->b_u_curhead = curbuf->b_u_oldhead;
		beep_flush();
		if (count == startcount - 1)
		{
		    MSG(_("Already at oldest change"));
		    return;
		}
		break;
	    }

	    u_undoredo(TRUE);
	}
	else
	{
	    if (curbuf->b_u_curhead == NULL || p_ul <= 0)
	    {
		beep_flush();
		if (count == startcount - 1)
		{
		    MSG(_("Already at newest change"));
		    return;
		}
		break;
	    }

	    u_undoredo(FALSE);


	    if (curbuf->b_u_curhead->uh_prev.ptr == NULL)
		curbuf->b_u_newhead = curbuf->b_u_curhead;
	    curbuf->b_u_curhead = curbuf->b_u_curhead->uh_prev.ptr;
	}
    }
    u_undo_end(undo_undoes, FALSE);
}
