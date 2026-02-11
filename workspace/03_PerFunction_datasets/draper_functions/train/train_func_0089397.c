scroll_attachment(char *title, STORE_S *store, SourceType src, HANDLE_S *handles, ATTACH_S *a, int flags)
{
    SCROLL_S  sargs;

    memset(&sargs, 0, sizeof(SCROLL_S));
    sargs.text.text    = so_text(store);
    sargs.text.src     = src;
    sargs.text.desc    = "attachment";
    sargs.text.handles = handles;
    sargs.bar.title    = title;
    sargs.proc.tool    = process_attachment_cmd;
    sargs.proc.data.p  = (void *) a;
    sargs.help.text    = h_mail_text_att_view;
    sargs.help.title   = _("HELP FOR ATTACHED TEXT VIEW");
    sargs.keys.menu    = &att_view_keymenu;
    setbitmap(sargs.keys.bitmap);


    if(flags & DA_FROM_VIEW){
	att_view_keymenu.keys[ATV_BACK_KEY].label = N_("MsgText");
    }
    else{
	att_view_keymenu.keys[ATV_BACK_KEY].label = N_("AttchIndex");
    }

    if(!handles){
	clrbitn(ATV_VIEW_HILITE, sargs.keys.bitmap);
	clrbitn(ATV_PREV_URL, sargs.keys.bitmap);
	clrbitn(ATV_NEXT_URL, sargs.keys.bitmap);
    }

    if(F_OFF(F_ENABLE_PIPE, ps_global))
      clrbitn(ATV_PIPE_KEY, sargs.keys.bitmap);

    if(!(a->body->type == TYPETEXT || MIME_MSG_A(a) || MIME_DGST_A(a)))
      clrbitn(ATV_PRINT_KEY, sargs.keys.bitmap);


    if(MIME_MSG_A(a)){
	if(F_OFF(F_ENABLE_BOUNCE, ps_global))
	  clrbitn(ATV_BOUNCE_KEY, sargs.keys.bitmap);
    }
    else{
	clrbitn(ATV_BOUNCE_KEY, sargs.keys.bitmap);
	clrbitn(ATV_REPLY_KEY, sargs.keys.bitmap);
	clrbitn(ATV_EXPORT_KEY, sargs.keys.bitmap);
    }

    sargs.use_indexline_color = 1;

    if(DA_RESIZE & flags)
      sargs.resize_exit = 1;

#ifdef	_WINDOWS
    scrat_attachp    = a;
    sargs.mouse.popup = scroll_att_popup;
#endif

    return(scrolltool(&sargs));
}
