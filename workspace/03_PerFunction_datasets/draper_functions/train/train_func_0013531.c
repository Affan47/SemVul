gsb_form_set_sensitive ( gboolean split,
                        gboolean split_child)
{
    GSList *tmp_list;


    if (!split
	&&
	!split_child)
	return FALSE;

    tmp_list = gsb_form_widget_get_list ();

    while (tmp_list)
    {
	struct_element *element;

	element = tmp_list -> data;


	if (split)
	{
	    switch (element -> element_number)
	    {
		case TRANSACTION_FORM_BUDGET:
		case TRANSACTION_FORM_VOUCHER:
		    gtk_widget_set_sensitive ( element -> element_widget,
					       FALSE );
		    break;
	    }
	}


	if ( split_child )
	{

	    switch (element -> element_number)
	    {
		case TRANSACTION_FORM_DATE:
		case TRANSACTION_FORM_VALUE_DATE:
		case TRANSACTION_FORM_PARTY:
		case TRANSACTION_FORM_DEVISE:
		case TRANSACTION_FORM_CHANGE:
		case TRANSACTION_FORM_TYPE:
		case TRANSACTION_FORM_CHEQUE:
		case TRANSACTION_FORM_BANK:
		    gtk_widget_set_sensitive ( element -> element_widget,
					       FALSE );
		    break;
	    }

	    gtk_widget_hide (gsb_form_get_scheduler_part ());
	}
	tmp_list = tmp_list -> next;
    }
    return FALSE;
}
