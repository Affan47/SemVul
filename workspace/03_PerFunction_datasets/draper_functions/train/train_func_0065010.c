mm_exists(MAILSTREAM *stream, long unsigned int number)
{
    long     new_this_call, n;
    int	     exbits = 0, lflags = 0;
    MSGNO_S *msgmap;

#ifdef DEBUG
    if(ps_global->debug_imap > 1 || ps_global->debugmem)
      dprint((3, "=== mm_exists(%lu,%s) called ===\n", number,
     !stream ? "(no stream)" : !stream->mailbox ? "(null)" : stream->mailbox));
#endif

    msgmap = sp_msgmap(stream);
    if(!msgmap)
      return;

    if(mn_get_nmsgs(msgmap) != (long) number){
	sp_set_mail_box_changed(stream, 1);

	if(ps_global->mail_stream == stream)
	  ps_global->mangled_header = 1;
    }

    if(mn_get_nmsgs(msgmap) < (long) number){
	new_this_call = (long) number - mn_get_nmsgs(msgmap);
	sp_set_new_mail_count(stream,
			      sp_new_mail_count(stream) + new_this_call);
	sp_set_recent_since_visited(stream,
			      sp_recent_since_visited(stream) + new_this_call);

	mn_add_raw(msgmap, new_this_call);


	for(n = 0; n < new_this_call; n++, number--){
	    if(msgno_exceptions(stream, number, "0", &exbits, FALSE))
	      exbits |= MSG_EX_RECENT;
	    else
	      exbits = MSG_EX_RECENT;

	    msgno_exceptions(stream, number, "0", &exbits, TRUE);

	    if(SORT_IS_THREADED(msgmap))
	      lflags |= MN_USOR;


	    lflags |= (any_lflagged(msgmap, MN_HIDE) ? MN_HIDE : 0);
	    if(lflags)
	      set_lflag(stream, msgmap, mn_get_total(msgmap) - n, lflags, 1);
	}
    }
}
