Index_Address_list_refine_recur(
            Index_Address *address_list,
            gint address_list_start, gint address_list_len,
            Index_Interval *interval_list,
            gint interval_list_start, gint interval_list_len,
            Index_Address *refined_address_list, gint *refined_address_list_len){
    register gint i, move, interval_mid;
    if(Index_Address_lt_Interval_start(&address_list[address_list_start],
                                       &interval_list[interval_list_start])){
        move = Index_Address_list_trim_start(address_list, address_list_start,
                                       address_list_len,
                                       &interval_list[interval_list_start]);
        address_list_start += move;
        address_list_len -= move;
        }
    if(Index_Address_gt_Interval_end(
                &address_list[address_list_start+address_list_len-1],
                &interval_list[interval_list_start+interval_list_len-1])){
        move = Index_Address_list_trim_end(address_list,
            address_list_start, address_list_len,
            &interval_list[interval_list_start+interval_list_len-1]);
        address_list_len -= move;
        }
    if(!address_list_len)
        return;
    if(interval_list_len == 1){
        for(i = 0; i < address_list_len; i++){
            refined_address_list[(*refined_address_list_len)].sequence_id
                = address_list[address_list_start+i].sequence_id;
            refined_address_list[(*refined_address_list_len)].position
                = address_list[address_list_start+i].position;
            (*refined_address_list_len)++;
            }
    } else {
        interval_mid = interval_list_len >> 1;
        if(interval_mid)
            Index_Address_list_refine_recur(address_list, address_list_start,
                                 address_list_len, interval_list,
                                 interval_list_start, interval_mid,
                                 refined_address_list, refined_address_list_len);
        if(interval_list_len-interval_mid)
            Index_Address_list_refine_recur(address_list, address_list_start,
                                 address_list_len, interval_list,
                                 interval_list_start+interval_mid,
                                 interval_list_len-interval_mid,
                                 refined_address_list, refined_address_list_len);
        }
    return;
    }
