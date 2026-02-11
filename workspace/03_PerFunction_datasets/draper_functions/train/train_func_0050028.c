flip_inv(int state)
{
    extern char *_setinverse, *_clearinverse;

    if((pinvstate = state) == TRUE){
	if(_setinverse != NULL)
	  putpad(_setinverse);
    }
    else{


	if(_clearinverse != NULL){
	    if(!color_blasted_by_attrs)
	      color_blasted_by_attrs = pico_get_cur_color();

	    _force_fg_color_change = _force_bg_color_change = 1;
	    putpad(_clearinverse);
	    pboldstate = (pboldstate == FALSE) ?  pboldstate : A_UNKNOWN;
	    pulstate = (pulstate == FALSE) ?  pulstate : A_UNKNOWN;
	    rev_color_state = A_UNKNOWN;
	}
    }
}
