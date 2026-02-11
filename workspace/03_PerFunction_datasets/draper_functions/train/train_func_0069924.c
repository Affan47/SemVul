pine_mail_copy_full(MAILSTREAM *stream, char *sequence, char *mailbox, long int options)
{
    MAILSTREAM *ourstream = NULL;
    long        return_val;
    long openflags = (OP_HALFOPEN | OP_SILENT | SP_USEPOOL | SP_TEMPUSE);
    char        source[MAILTMPLEN], *target = NULL;
    char        mailbox_nodelim[MAILTMPLEN];
    int         delim;
    DRIVER     *d;

    dprint((7, "pine_mail_copy_full: copying to \"%s\"%s\n",
	       mailbox ? mailbox : "(NULL)",
	       stream ? "" : " (stream was NULL)"));


    if(mailbox && (delim = get_folder_delimiter(mailbox)) != '\0'){
	size_t len;

	len = strlen(mailbox);
	if(mailbox[len-1] == delim){
	    strncpy(mailbox_nodelim, mailbox, MIN(len-1,sizeof(mailbox_nodelim)-1));
	    mailbox_nodelim[MIN(len-1,sizeof(mailbox_nodelim)-1)] = '\0';
	    mailbox = mailbox_nodelim;
	}
    }

    if(check_for_move_mbox(mailbox, source, sizeof(source), &target)){
	mailbox = target;
	dprint((7,
	   "pine_mail_copy_full: #move special case, copying to \"%s\"\n",
		   mailbox ? mailbox : "(NULL)"));
    }


    if((F_ON(F_PREFER_ALT_AUTH, ps_global)
       || (ps_global->debug_imap > 3 || ps_global->debugmem))){

	if((d = mail_valid (NIL, mailbox, (char *) NIL))
	   && !strcmp(d->name, "imap")){

	    if(F_ON(F_PREFER_ALT_AUTH, ps_global))
	      openflags |= OP_TRYALT;
	}
    }

    if(!stream)
      stream = sp_stream_get(mailbox, SP_MATCH);
    if(!stream)
      stream = sp_stream_get(mailbox, SP_SAME);

    if(!stream){


	if((d = mail_valid (NIL, mailbox, (char *) NIL))
	   && !strcmp(d->name, "imap")){

	    stream = pine_mail_open(NULL, mailbox, openflags, NULL);
	    ourstream = stream;
	}
    }

    return_val = mail_copy_full(stream, sequence, mailbox, options);

    if(ourstream)
      pine_mail_close(ourstream);

    return(return_val);
}
