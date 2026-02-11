index_scroll_up(long int scroll_count)
{
    static short bad_timing = 0;
    long i, j, k;
    long cur;

    if(bad_timing)
      return(FALSE);

    bad_timing = 1;

    j = -1L;
    for(k = i = current_index_state->msg_at_top; ; i--){


	if(!msgline_hidden(current_index_state->stream,
			   current_index_state->msgmap, i, 0)){

	    k = i;

	    if (++j >= scroll_count) {

		current_index_state->msg_at_top = k;
		break;
	    }
	}


	if (i <= 1L){
	    current_index_state->msg_at_top = k;
	    break;
	}
    }


    if(mn_total_cur(current_index_state->msgmap) == 1L) {
	j = 0L;
	cur = mn_get_cur (current_index_state->msgmap);
	for (	i = current_index_state->msg_at_top;
		i <= mn_get_total(current_index_state->msgmap);
		++i) {
	    if(!msgline_hidden(current_index_state->stream,
			       current_index_state->msgmap, i, 0)){
	        if (++j >= current_index_state->lines_per_page) {
		    k = i;
		    break;
	        }
		if (i == cur)
		    break;
	    }
        }
	if (i != cur)
	    mn_set_cur(current_index_state->msgmap, k);
    }


    bad_timing = 0;
    return (TRUE);
}
