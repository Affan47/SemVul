cmd_delete_action(struct pine *state, MSGNO_S *msgmap, CmdWhere in_index)
{
    int	  opts;
    long  msgno;
    char *rv = NULL;

    msgno = mn_get_cur(msgmap);
    advance_cur_after_delete(state, state->mail_stream, msgmap, in_index);

    if(IS_NEWS(state->mail_stream)
       || ((state->context_current->use & CNTXT_INCMNG)
	   && context_isambig(state->cur_folder))){

	opts = (NSF_TRUST_FLAGS | NSF_SKIP_CHID);
	if(in_index == View)
	  opts &= ~NSF_SKIP_CHID;

	(void)next_sorted_flagged(F_UNDEL|F_UNSEEN, state->mail_stream, msgno, &opts);
	if(!(opts & NSF_FLAG_MATCH)){
	    char nextfolder[MAXPATH];

	    strncpy(nextfolder, state->cur_folder, sizeof(nextfolder));
	    nextfolder[sizeof(nextfolder)-1] = '\0';
	    rv = next_folder(NULL, nextfolder, sizeof(nextfolder), nextfolder,
			     state->context_current, NULL, NULL)
		   ? ".  Press TAB for next folder."
		   : ".  No more folders to TAB to.";
	}
    }

    return(rv);
}
