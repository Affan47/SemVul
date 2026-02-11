list_mgmt_screen(STORE_S *html)
{
    int		    cmd = MC_NONE;
    long	    offset = 0L;
    char	   *error = NULL;
    STORE_S	   *store;
    HANDLE_S	   *handles = NULL;
    gf_io_t	    gc, pc;

    do{
	so_seek(html, 0L, 0);
	gf_set_so_readc(&gc, html);

	init_handles(&handles);

	if((store = so_get(CharStar, NULL, EDIT_ACCESS)) != NULL){
	    gf_set_so_writec(&pc, store);
	    gf_filter_init();

	    gf_link_filter(gf_html2plain,
			   gf_html2plain_opt(NULL, ps_global->ttyo->screen_cols,
					     non_messageview_margin(), &handles, NULL, 0));

	    error = gf_pipe(gc, pc);

	    gf_clear_so_writec(store);

	    if(!error){
		SCROLL_S	sargs;

		memset(&sargs, 0, sizeof(SCROLL_S));
		sargs.text.text	   = so_text(store);
		sargs.text.src	   = CharStar;
		sargs.text.desc	   = "list commands";
		sargs.text.handles = handles;
		if(offset){
		    sargs.start.on	   = Offset;
		    sargs.start.loc.offset = offset;
		}

		sargs.bar.title	   = _("MAIL LIST COMMANDS");
		sargs.bar.style	   = MessageNumber;
		sargs.resize_exit  = 1;
		sargs.help.text	   = h_special_list_commands;
		sargs.help.title   = _("HELP FOR LIST COMMANDS");
		sargs.keys.menu	   = &listmgr_keymenu;
		setbitmap(sargs.keys.bitmap);
		if(!handles){
		    clrbitn(LM_TRY_KEY, sargs.keys.bitmap);
		    clrbitn(LM_PREV_KEY, sargs.keys.bitmap);
		    clrbitn(LM_NEXT_KEY, sargs.keys.bitmap);
		}

		cmd = scrolltool(&sargs);
		offset = sargs.start.loc.offset;
	    }

	    so_give(&store);
	}

	free_handles(&handles);
	gf_clear_so_readc(html);
    }
    while(cmd == MC_RESIZE);
}
