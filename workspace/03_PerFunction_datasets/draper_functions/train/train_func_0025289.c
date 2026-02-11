Index_Address_list_refine(Index_Address *address_list,
                                      gint address_list_len,
                                      GArray *interval_list){
    register Index_Address *refined_address_list
        = g_new(Index_Address, address_list_len);
    register gint i;
    gint refined_address_list_len = 0;
    Index_Address_list_refine_recur(address_list, 0, address_list_len,
            (Index_Interval*)interval_list->data, 0, interval_list->len,
            refined_address_list, &refined_address_list_len);
    g_assert(refined_address_list_len <= address_list_len);


    for(i = 0; i < refined_address_list_len; i++){
        address_list[i].sequence_id = refined_address_list[i].sequence_id;
        address_list[i].position = refined_address_list[i].position;
        }
    g_free(refined_address_list);
    return refined_address_list_len;
    }
