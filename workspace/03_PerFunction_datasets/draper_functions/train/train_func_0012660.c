gsb_data_scheduled_get_last_white_number (void)
{
    gint last_number = 0;
    GSList *scheduled_list_tmp;

    scheduled_list_tmp = white_scheduled_list;

    while (scheduled_list_tmp)
    {
	struct_scheduled *scheduled;

	scheduled = scheduled_list_tmp -> data;
	if ( scheduled -> scheduled_number < last_number )
	    last_number = scheduled -> scheduled_number;

	scheduled_list_tmp = scheduled_list_tmp -> next;
    }


    if ( !last_number )
	last_number = -1;

    return last_number;
}
