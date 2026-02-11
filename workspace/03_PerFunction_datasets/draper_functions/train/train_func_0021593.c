gsb_data_payee_update_counters ( void )
{
    GSList *list_tmp_transactions;

    gsb_data_payee_reset_counters ();

    if ( etat.add_archive_in_total_balance )
        list_tmp_transactions = gsb_data_transaction_get_complete_transactions_list ();
    else
        list_tmp_transactions = gsb_data_transaction_get_transactions_list ();

    while ( list_tmp_transactions )
    {
	gint transaction_number_tmp;
	transaction_number_tmp = gsb_data_transaction_get_transaction_number (list_tmp_transactions -> data);

	gsb_data_payee_add_transaction_to_payee ( transaction_number_tmp );

	list_tmp_transactions = list_tmp_transactions -> next;
    }
}
