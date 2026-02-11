usr2_signal(int sig)
{
    char        c, *mbox, mboxbuf[20];
    int         i;
    MAILSTREAM *stream;
    NETMBX      mb;

    for(i = 0; i < ps_global->s_pool.nstream; i++){
	stream = ps_global->s_pool.streams[i];
	if(stream
	   && sp_flagged(stream, SP_LOCKED)
	   && !sp_dead_stream(stream)
	   && !stream->lock
	   && !stream->rdonly
	   && stream->mailbox
	   && (c = *stream->mailbox) != '{' && c != '*'){
	    pine_mail_check(stream);
	    stream->rdonly = 1;
	    (void) pine_mail_ping(stream);
	    mbox = stream->mailbox;
	    if(!strucmp(stream->mailbox, ps_global->inbox_name)
	       || !strcmp(stream->mailbox, ps_global->VAR_INBOX_PATH)
	       || !strucmp(stream->original_mailbox, ps_global->inbox_name)
	       || !strcmp(stream->original_mailbox, ps_global->VAR_INBOX_PATH))
	      mbox = "INBOX";
	    else if(mail_valid_net_parse(stream->mailbox, &mb) && mb.mailbox)
	      mbox = mb.mailbox;

	    q_status_message1(SM_ASYNC, 3, 7,
	     _("Another email program is accessing %s. Session now Read-Only."),
	     short_str((mbox && *mbox) ? mbox : "folder",
		       mboxbuf, sizeof(mboxbuf), 19, FrontDots));
	    dprint((1, "** folder %s went read-only **\n\n",
			stream->mailbox));
	}
    }
}
