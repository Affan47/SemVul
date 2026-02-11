gsb_form_scheduler_set_content_list ( GSList *content_list )
{
    GSList *list_tmp;
    gint account_number;

    account_number = gsb_form_scheduler_get_account ();

    list_tmp = content_list;


    while (list_tmp)
    {
	content_element *element;
	GSList *form_list;

	element = list_tmp -> data;


	if (!element)
	    continue;


	form_list = gsb_form_widget_get_list ();

	while (form_list)
	{
	    struct_element *form_element;

	    form_element = form_list -> data;

	    if (!GTK_WIDGET_VISIBLE (form_element -> element_widget)
		||
		form_element -> element_number != element -> element_number)
	    {
		form_list = form_list -> next;
		continue;
	    }

	    switch (form_element -> element_number)
	    {

		case TRANSACTION_FORM_DATE:
		case TRANSACTION_FORM_VALUE_DATE:
		case TRANSACTION_FORM_DEBIT:
		case TRANSACTION_FORM_CREDIT:
		case TRANSACTION_FORM_NOTES:
		case TRANSACTION_FORM_BANK:
		case TRANSACTION_FORM_VOUCHER:
		    gsb_form_entry_get_focus (form_element -> element_widget);
            if ( element -> element_string )
                gtk_entry_set_text ( GTK_ENTRY (form_element -> element_widget),
                                element -> element_string );
		    break;

		case TRANSACTION_FORM_TYPE:
		    gsb_payment_method_create_combo_list ( form_element -> element_widget,
							   gsb_data_payment_get_sign (element -> element_int),
							   account_number, 0, FALSE );
		    gsb_payment_method_set_combobox_history ( form_element -> element_widget,
							   gsb_data_payment_get_similar (element -> element_int, account_number), TRUE );
		    break;

		case TRANSACTION_FORM_CONTRA:
		    gsb_payment_method_create_combo_list ( form_element -> element_widget,
							   gsb_data_payment_get_sign (element -> element_int),
							   account_number, 0, TRUE );
		    gsb_payment_method_set_combobox_history ( form_element -> element_widget,
							   gsb_data_payment_get_similar (element -> element_int, account_number), TRUE );
			break;

		case TRANSACTION_FORM_EXERCICE:
		    gsb_fyear_set_combobox_history ( form_element -> element_widget,
						     element -> element_int );
		    break;

		case TRANSACTION_FORM_DEVISE:
		    gsb_currency_set_combobox_history ( form_element -> element_widget,
							element -> element_int );
		    break;


		case TRANSACTION_FORM_PARTY:
		case TRANSACTION_FORM_CATEGORY:
		case TRANSACTION_FORM_BUDGET:
		    gsb_form_entry_get_focus (form_element -> element_widget);
            if ( element -> element_string )
                gtk_combofix_set_text ( GTK_COMBOFIX ( form_element -> element_widget ),
                                element -> element_string );
		    break;
	    }
	    form_list = form_list -> next;
	}
	list_tmp = list_tmp -> next;
    }
}
