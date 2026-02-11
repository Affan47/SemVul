gsb_transactions_list_sort_by_transaction_date_and_no ( gint transaction_number_1,
                        gint transaction_number_2 )
{
    gint return_value;

    if ( !gsb_data_transaction_get_date (transaction_number_1) )
    {
    return 1;
    }
    if ( !gsb_data_transaction_get_date (transaction_number_2) )
    {
    return -1;
    }


    return_value = g_date_compare ( gsb_data_transaction_get_date (transaction_number_1),
                        gsb_data_transaction_get_date (transaction_number_2));


    if ( !return_value )
    return_value = transaction_number_1 - transaction_number_2;

    return return_value;
}
