gsb_account_property_change_currency ( GtkWidget *combobox,
                        gpointer null )
{
    gint account_number;
    gint new_currency_number;
    gint account_currency_number;
    gint result;
    GSList *list_tmp;
	gchar* tmpstr;

    account_number = gsb_gui_navigation_get_current_account ();

    account_currency_number = gsb_data_account_get_currency (account_number);

    new_currency_number = gsb_currency_get_currency_from_combobox (detail_devise_compte);

    if ( account_currency_number == new_currency_number )
        return FALSE;


    gsb_data_account_set_currency ( account_number,
				    new_currency_number );


    tmpstr = g_strdup_printf ( _("You are changing the currency of the account, do you want to change the currency of the transactions too ?\n(yes will change all the transactions currency from %s to %s, all the transactions with another currency will stay the same).\n\nArchived and reconcilied transactions will be left unmodified."),
				      gsb_data_currency_get_name (account_currency_number),
				      gsb_data_currency_get_name (new_currency_number));
    result = question_yes_no_hint ( _("Change the transactions currency"),
				    tmpstr,
				    GTK_RESPONSE_NO );
    g_free ( tmpstr );

    if (result)
    {


	list_tmp = gsb_data_transaction_get_transactions_list ();

	while ( list_tmp )
	{
	    gint transaction_number;
	    transaction_number = gsb_data_transaction_get_transaction_number (list_tmp -> data);

	    if ( gsb_data_transaction_get_account_number (transaction_number) == account_number
		 &&
		 gsb_data_transaction_get_currency_number (transaction_number) == account_currency_number
		 &&
		 gsb_data_transaction_get_marked_transaction (transaction_number) != OPERATION_RAPPROCHEE)
		gsb_data_transaction_set_currency_number ( transaction_number,
							   new_currency_number );
	    list_tmp = list_tmp -> next;
	}
    }

    transaction_list_update_element (ELEMENT_CREDIT);
    transaction_list_update_element (ELEMENT_DEBIT);
    transaction_list_update_element (ELEMENT_AMOUNT);


    transaction_list_set_balances ();


    gsb_data_account_colorize_current_balance ( account_number );

    return FALSE;
}
