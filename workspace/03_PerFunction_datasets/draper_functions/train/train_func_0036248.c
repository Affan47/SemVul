Index_AddressList_create(gint freq_count){
    register Index_AddressList *address_list = g_new(Index_AddressList, 1);
    address_list->found = 0;
    address_list->address_list = g_new(Index_Address, freq_count);
    return address_list;
    }
