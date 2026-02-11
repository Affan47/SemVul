index_scroll_to_pos (long int pos)
{
    static short bad_timing = 0;
    long	i, j, k;

    if(bad_timing)
      return (FALSE);


    for(i=pos; i <= mn_get_total(current_index_state->msgmap); i++) {
      if(!msgline_hidden(current_index_state->stream,
			 current_index_state->msgmap, i, 0)){
	  current_index_state->msg_at_top = i;
	  break;
      }
    }


    if (mn_total_cur(current_index_state->msgmap) == 1L) {
      if (current_index_state->msg_at_top >
			      mn_get_cur (current_index_state->msgmap)) {

	mn_set_cur(current_index_state->msgmap,current_index_state->msg_at_top);
      }
      else {


        for(  i = current_index_state->msg_at_top,
	        j = current_index_state->lines_per_page;
	      i != mn_get_cur(current_index_state->msgmap) &&
		i <= mn_get_total(current_index_state->msgmap) &&
		j > 0L;
	      i++) {
	    if(!msgline_hidden(current_index_state->stream,
			       current_index_state->msgmap, i, 0)){
	        j--;
	        k = i;
            }
        }
	if(j <= 0L)

	    mn_set_cur(current_index_state->msgmap, k);
      }
    }

    bad_timing = 0;
    return (TRUE);
}
