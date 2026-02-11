ex_oldfiles(eap)
    exarg_T	*eap UNUSED;
{
    list_T	*l = vimvars[VV_OLDFILES].vv_list;
    listitem_T	*li;
    int		nr = 0;

    if (l == NULL)
	msg((char_u *)_("No old files"));
    else
    {
	msg_start();
	msg_scroll = TRUE;
	for (li = l->lv_first; li != NULL && !got_int; li = li->li_next)
	{
	    msg_outnum((long)++nr);
	    MSG_PUTS(": ");
	    msg_outtrans(get_tv_string(&li->li_tv));
	    msg_putchar('\n');
	    out_flush();
	    ui_breakcheck();
	}

	got_int = FALSE;

#ifdef FEAT_BROWSE_CMD
	if (cmdmod.browse)
	{
	    quit_more = FALSE;
	    nr = prompt_for_number(FALSE);
	    msg_starthere();
	    if (nr > 0)
	    {
		char_u *p = list_find_str(get_vim_var_list(VV_OLDFILES),
								    (long)nr);

		if (p != NULL)
		{
		    p = expand_env_save(p);
		    eap->arg = p;
		    eap->cmdidx = CMD_edit;
		    cmdmod.browse = FALSE;
		    do_exedit(eap, NULL);
		    vim_free(p);
		}
	    }
	}
#endif
    }
}
