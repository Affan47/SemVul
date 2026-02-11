new_mail_mess(MAILSTREAM *stream, long int number, long int max_num, int for_new_mail_win)
{
    char      subject[MAILTMPLEN+1], subjtext[MAILTMPLEN+1], from[MAILTMPLEN+1],
	     *folder = NULL, intro[MAILTMPLEN+1];
    ENVELOPE *e = NULL;

    if(stream)
      e = pine_mail_fetchstructure(stream, max_num, NULL);

    if(stream){
	if(sp_flagged(stream, SP_INBOX))
	  folder = NULL;
	else{
	    folder = STREAMNAME(stream);
	    if(folder[0] == '?' && folder[1] == '\0')
	      folder = NULL;
	}
    }

    format_new_mail_msg(folder, number, e, intro, from, subject, subjtext, sizeof(subject));

    if(!for_new_mail_win)
      q_status_message5(SM_ASYNC | SM_DING, 0, 60,
		      "%s%s%s%.80s%.80s", intro,
 		      from && from[0] ? ((number > 1L) ? " Most recent f" : " F") : "",
 		      from && from[0] ? "rom " : "",
 		      from && from[0] ? from : "",
		      subjtext);
#if (!defined(DOS) && !defined(OS2) && !defined(LEAVEOUTFIFO)) || defined(_WINDOWS)
    else {
	int is_us = 0;
	ADDRESS *tadr;

	if(e)
	  for(tadr = e->to; tadr; tadr = tadr->next)
	    if(address_is_us(tadr, ps_global)){
		is_us = 1;
		break;
	    }
#ifdef _WINDOWS
	mswin_newmailwin(is_us, from, subject, folder);
#else
	newmailfifo(is_us, from, subject, folder);
#endif
    }
#endif

    if(pith_opt_icon_text){
	if(F_ON(F_ENABLE_XTERM_NEWMAIL, ps_global)
	   && F_ON(F_ENABLE_NEWMAIL_SHORT_TEXT, ps_global)){
	    long inbox_nm;
	    if(!sp_flagged(stream, SP_INBOX)
	       && (inbox_nm = sp_mail_since_cmd(sp_inbox_stream()))){
		snprintf(tmp_20k_buf, SIZEOF_20KBUF, "[%ld, %ld] %s",
			 inbox_nm > 1L ? inbox_nm : 1L,
			 number > 1L ? number: 1L,
			 ps_global->pine_name);
	    }
	    else
	      snprintf(tmp_20k_buf, SIZEOF_20KBUF, "[%ld] %s", number > 1L ? number: 1L,
		       ps_global->pine_name);
	}
	else
	  snprintf(tmp_20k_buf, SIZEOF_20KBUF, "%s%s%s%.80s", intro,
		   from && from[0] ? ((number > 1L) ? " Most recent f" : " F") : "",
		   from && from[0] ? "rom " : "",
		   from && from[0] ? from : "");

	(*pith_opt_icon_text)(tmp_20k_buf, IT_NEWMAIL);
    }
}
