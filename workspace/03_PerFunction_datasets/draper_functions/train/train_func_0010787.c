cmd_delete(struct pine *state, MSGNO_S *msgmap, int copts,
	   char *(*cmd_action_f)(struct pine *, MSGNO_S *))
{
    int	  lastmsg, rv = 0;
    long  msgno, del_count = 0L, new;
    char *sequence = NULL, prompt[128];

    dprint((4, "\n - delete message -\n"));
    if(!(any_messages(msgmap, NULL, "to Delete")
	 && can_set_flag(state, "delete", state->mail_stream->perm_deleted)))
      return rv;

    rv++;

    if(sp_io_error_on_stream(state->mail_stream)){
	sp_set_io_error_on_stream(state->mail_stream, 0);
	pine_mail_check(state->mail_stream);
    }

    if(MCMD_ISAGG(copts)){
	sequence = selected_sequence(state->mail_stream, msgmap, &del_count, 0);
	snprintf(prompt, sizeof(prompt), "%ld%s message%s marked for deletion",
		del_count, (copts  & MCMD_AGG_2) ? "" : " selected", plural(del_count));
    }
    else{
	long rawno;

	msgno	  = mn_get_cur(msgmap);
	rawno     = mn_m2raw(msgmap, msgno);
	del_count = 1L;
	sequence  = cpystr(long2string(rawno));
	lastmsg	  = (msgno >= mn_get_total(msgmap));
	snprintf(prompt, sizeof(prompt), "%s%s marked for deletion",
		lastmsg ? "Last message" : "Message ",
		lastmsg ? "" : long2string(msgno));
    }

    dprint((3, "DELETE: msg %s\n", sequence ? sequence : "?"));
    new = sp_new_mail_count(state->mail_stream);
    mail_flag(state->mail_stream, sequence, "\\DELETED", ST_SET);
    fs_give((void **) &sequence);
    if(new != sp_new_mail_count(state->mail_stream))
      process_filter_patterns(state->mail_stream, state->msgmap,
			      sp_new_mail_count(state->mail_stream));

    if(cmd_action_f){
	char *rv;

	if((rv = (*cmd_action_f)(state, msgmap)) != NULL)
	  strncat(prompt, rv, sizeof(prompt) - strlen(prompt)- 1);
    }

    if(!(copts & MCMD_SILENT))
      q_status_message(SM_ORDER, 0, 3, prompt);

    return rv;
}
