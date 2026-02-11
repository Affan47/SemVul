process_attachment_cmd(int cmd, MSGNO_S *msgmap, SCROLL_S *sparms)
{
    int rv = 0, n;
    long rawno = mn_m2raw(msgmap, mn_get_cur(msgmap));
#define	AD(X)	((ATTACH_S *) (X)->proc.data.p)

    switch(cmd){
      case MC_EXIT :
	rv = 1;
	break;

      case MC_QUIT :
	ps_global->next_screen = quit_screen;
	break;

      case MC_MAIN :
	ps_global->next_screen = main_menu_screen;
	break;

      case MC_REPLY :
	reply_msg_att(ps_global->mail_stream, rawno, sparms->proc.data.p);
	break;

      case MC_FORWARD :
	forward_attachment(ps_global->mail_stream, rawno, sparms->proc.data.p);
	break;

      case MC_BOUNCE :
	bounce_msg_att(ps_global->mail_stream, rawno, AD(sparms)->number,
		       AD(sparms)->body->nested.msg->env->subject);
	ps_global->mangled_footer = 1;
	break;

      case MC_DELETE :
	delete_attachment(rawno, sparms->proc.data.p);
	break;

      case MC_UNDELETE :
	if(undelete_attachment(rawno, sparms->proc.data.p, &n))
	  q_status_message1(SM_ORDER, 0, 3,
			    "Part %s UNdeleted", AD(sparms)->number);

	break;

      case MC_SAVE :
	save_attachment(-FOOTER_ROWS(ps_global), rawno, sparms->proc.data.p);
	ps_global->mangled_footer = 1;
	break;

      case MC_EXPORT :
	export_attachment(-FOOTER_ROWS(ps_global), rawno, sparms->proc.data.p);
	ps_global->mangled_footer = 1;
	break;

      case MC_PRINTMSG :
	print_attachment(-FOOTER_ROWS(ps_global), rawno, sparms->proc.data.p);
	ps_global->mangled_footer = 1;
	break;

      case MC_PIPE :
	pipe_attachment(rawno, sparms->proc.data.p);
	ps_global->mangled_footer = 1;
	break;

      case MC_FULLHDR :
	ps_global->full_header++;
	if(ps_global->full_header == 1){
	    if(!(ps_global->quote_suppression_threshold
	         && (ps_global->some_quoting_was_suppressed )))
	      ps_global->full_header++;
	}
	else if(ps_global->full_header > 2)
	  ps_global->full_header = 0;

	switch(ps_global->full_header){
	  case 0:
	    q_status_message(SM_ORDER, 0, 3,
			     _("Display of full headers is now off."));
	    break;

	  case 1:
	    q_status_message1(SM_ORDER, 0, 3,
			  _("Quotes displayed, use %s to see full headers"),
			  F_ON(F_USE_FK, ps_global) ? "F9" : "H");
	    break;

	  case 2:
	    q_status_message(SM_ORDER, 0, 3,
			     _("Display of full headers is now on."));
	    break;

	}

	rv = 1;
	break;

      default:
	panic("Unexpected command case");
	break;
    }

    return(rv);
}
