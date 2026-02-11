gsb_data_transaction_save_transaction_pointer ( gpointer transaction )
{


    if ( transaction == transaction_buffer[0]
	 ||
	 transaction == transaction_buffer[1] )
	return TRUE;

    current_transaction_buffer = !current_transaction_buffer;
    transaction_buffer[current_transaction_buffer] = transaction;
    return TRUE;
}
