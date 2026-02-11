make_temp_mtg_of_all_block( Block *first_block, Hmdf_information **hmdf_info_list_pp )
{
    Block           *bpt;
    Hmdf_information *hmdf_info;
    Hmdf_information *list_end;

    for( bpt = first_block; bpt; bpt = bpt->next ){
	if( bpt->inner != NULL ){
	    make_temp_mtg_of_all_block( bpt->inner, hmdf_info_list_pp );
	}

	hmdf_info = get_info_about_para( bpt );

        if( hmdf_info != NULL ){
            if( *hmdf_info_list_pp == NULL ){
                *hmdf_info_list_pp = hmdf_info;
            }else{
                for( list_end = *hmdf_info_list_pp; list_end->next;
                     list_end = list_end->next );
                list_end->next = hmdf_info;
                hmdf_info->prev = list_end;
            }
	}
    }
}
