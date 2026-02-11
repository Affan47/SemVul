chk_overlap_type(Array_subscript_info *target_array_sub,
			      Array_subscript_info *search_array_sub,
			      Array_subscript_info *ol_range)
{
    Overlap_type rtn;
    int ol_size;

    ol_size = chk_overlap_size(ol_range);

    if(ol_size == 0){
	if(chk_range_seq(target_array_sub,search_array_sub) == 1){
	    rtn = T_SEQ_S;
	}else if(chk_range_seq(target_array_sub,search_array_sub) == -1){
	    rtn = S_SEQ_T;
	}else{
	    rtn = NO_OVERLAP;
	}
    }else if(chk_array_equal(target_array_sub,search_array_sub) == TRUE){
	rtn = T_EQ_S;
    }else if(chk_array_over(target_array_sub,search_array_sub,ol_range) == 1){
	rtn = TARGET;
    }else if(chk_array_over(target_array_sub,search_array_sub,ol_range) == -1){
	rtn = SEARCH;
    }else if(chk_array_in_line(target_array_sub,search_array_sub) == 1){
	rtn = TARGET_SEARCH;
    }else if(chk_array_in_line(target_array_sub,search_array_sub) == -1){
	rtn = SEARCH_TARGET;
    }else{
	rtn =  CANNOT_ANA;
    }

    return rtn;
}
