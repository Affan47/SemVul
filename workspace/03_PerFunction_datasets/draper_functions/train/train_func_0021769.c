init_att_progress(char *msg, MAILSTREAM *stream, struct mail_bodystruct *body)
{
    if((save_att_length = body->size.bytes) != 0){

	if(body->type == TYPETEXT && ps_global->VAR_DISPLAY_FILTERS)
	  save_att_length += body->size.bytes;


	if(stream && stream->mailbox && IS_REMOTE(stream->mailbox)
	   && !((body->type == TYPETEXT && body->contents.text.data)
		|| ((body->type == TYPEMESSAGE)
		    && body->nested.msg && body->nested.msg->text.text.data)
		|| body->contents.text.data))
	  save_att_length += body->size.bytes;

	gf_filter_init();
	pine_gets_bytes(1);
	save_att_piped(1);
	return(busy_cue(msg, save_att_percent, 0));
    }

    return(0);
}
