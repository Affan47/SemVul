gsb_data_category_get_sub_category_structure ( gint no_category,
                        gint no_sub_category )
{
    GSList *tmp;
    struct_category *category;


    if (!no_sub_category)
	return NULL;


    if ( sub_category_buffer
	 &&
	 sub_category_buffer -> mother_category_number == no_category
	 &&
	 sub_category_buffer -> sub_category_number == no_sub_category )
	return sub_category_buffer;

    category = gsb_data_category_get_structure ( no_category );
    if ( ! category )
	return NULL;

    tmp = category -> sub_category_list;

    while ( tmp )
    {
	struct_sub_category *sub_category;

	sub_category = tmp -> data;

	if ( sub_category -> sub_category_number == no_sub_category )
	{
	    sub_category_buffer = sub_category;
	    return sub_category;
	}
	tmp = tmp -> next;
    }
    return NULL;
}
