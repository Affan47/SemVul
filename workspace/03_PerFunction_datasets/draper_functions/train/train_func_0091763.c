gsb_transactions_list_sort_by_financial_year ( gint transaction_number_1,
                        gint transaction_number_2 )
{
    gint return_value;

    if ( gsb_data_transaction_get_financial_year_number ( transaction_number_1)== gsb_data_transaction_get_financial_year_number ( transaction_number_2))
	return_value = gsb_transactions_list_sort_by_transaction_date_and_no(transaction_number_1, transaction_number_2);
    else
    {
	GDate *date_1;
	GDate *date_2;

	date_1 = gsb_data_fyear_get_beginning_date (gsb_data_transaction_get_financial_year_number ( transaction_number_1));
	date_2 = gsb_data_fyear_get_beginning_date (gsb_data_transaction_get_financial_year_number ( transaction_number_2));

	if ( date_1 )
	{
	    if ( date_2 )
		return_value = g_date_compare ( date_1,
						date_2 );
	    else
		return_value = 1;
	}
	else
	{
	    if ( date_2 )
		return_value = -1;
	    else
		return_value = 0;
	}
    }

    if ( return_value )
	return return_value;
    else
	return gsb_transactions_list_sort_by_transaction_date_and_no(transaction_number_1, transaction_number_2);

}
