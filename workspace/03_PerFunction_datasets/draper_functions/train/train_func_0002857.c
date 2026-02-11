message_format_for_pico(long int n, int (*f) (int))
{
    ENVELOPE *e;
    BODY     *b;
    char     *old_quote = NULL;
    long      rv = n;

    if(!(n > 0L && n <= mn_get_total(ps_global->msgmap)
       && (e = pine_mail_fetchstructure(ps_global->mail_stream,
				        mn_m2raw(ps_global->msgmap, n), &b)))){
	q_status_message(SM_ORDER|SM_DING,3,3,"Error inserting Message");
	flush_status_messages(0);
	return(0L);
    }


    old_quote = pbf->quote_str;
    pbf->quote_str = reply_quote_str(e);


    reply_delimiter(e, NULL, f);


    if(!format_message(mn_m2raw(ps_global->msgmap, n), e, b, NULL,
		       FM_NEW_MESS | FM_DISPLAY | FM_NOCOLOR | FM_NOINDENT, f)){
	q_status_message(SM_ORDER|SM_DING,3,3,"Error inserting Message");
	flush_status_messages(0);
	rv = 0L;
    }

    fs_give((void **)&pbf->quote_str);
    pbf->quote_str = old_quote;
    return(rv);
}
