exe_commands(parmp)
    mparm_T	*parmp;
{
    int		i;


    msg_scroll = TRUE;
    if (parmp->tagname == NULL && curwin->w_cursor.lnum <= 1)
	curwin->w_cursor.lnum = 0;
    sourcing_name = (char_u *)"command line";
#ifdef FEAT_EVAL
    current_SID = SID_CARG;
#endif
    for (i = 0; i < parmp->n_commands; ++i)
    {
	do_cmdline_cmd(parmp->commands[i]);
	if (parmp->cmds_tofree[i])
	    vim_free(parmp->commands[i]);
    }
    sourcing_name = NULL;
#ifdef FEAT_EVAL
    current_SID = 0;
#endif
    if (curwin->w_cursor.lnum == 0)
	curwin->w_cursor.lnum = 1;

    if (!exmode_active)
	msg_scroll = FALSE;

#ifdef FEAT_QUICKFIX

    if (parmp->edit_type == EDIT_QF)
	qf_jump(NULL, 0, 0, FALSE);
#endif
    TIME_MSG("executing command arguments");
}
