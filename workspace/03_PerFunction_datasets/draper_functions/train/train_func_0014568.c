Index_Address_list_trim_end(Index_Address *address_list,
                                        gint address_list_start,
                                        gint address_list_len,
                                        Index_Interval *limit){
    register gint left = address_list_start,
                  right = address_list_start+address_list_len-1, mid;
    while(left < right){
        mid = (left+right) >> 1;
        if(Index_Address_lt_Interval_end(&address_list[mid], limit)){
            left = mid + 1;
        } else {
            if((mid == address_list_start)
            || (Index_Address_lt_Interval_end(&address_list[mid-1], limit)))
                return address_list_start+address_list_len-mid;
            right = mid;
            }
        }
    return address_list_len;
    }
