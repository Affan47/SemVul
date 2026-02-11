agg_select_all(MAILSTREAM *stream, MSGNO_S *msgmap, long int *diff, int on)
{
    long i;
    int  hidden = any_lflagged(msgmap, MN_HIDE) > 0L;

    for(i = 1L; i <= mn_get_total(msgmap); i++){
	if(on){
	  set_lflag(stream, msgmap, i, MN_SLCT, 1);
	}
	else {
	    if(get_lflag(stream, msgmap, i, MN_SLCT)){
		if(diff)
		  (*diff)++;

		set_lflag(stream, msgmap, i, MN_SLCT, 0);
	    }
	    else if(hidden)
	      set_lflag(stream, msgmap, i, MN_HIDE, 0);
	}
    }
}
