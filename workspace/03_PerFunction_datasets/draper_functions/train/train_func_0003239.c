_gsb_data_account_free ( struct_account* account )
{
    if ( ! account )
        return;
    if ( account -> account_id )
	    g_free ( account -> account_id );
    if ( account -> account_name )
	    g_free ( account -> account_name );
    if ( account -> name_icon )
	    g_free ( account -> name_icon );
    if ( account -> comment )
	    g_free ( account -> comment );
    if ( account -> holder_name )
	    g_free ( account -> holder_name );
    if ( account -> holder_address )
	    g_free ( account -> holder_address );
    if ( account -> bank_branch_code )
	    g_free ( account -> bank_branch_code );
    if ( account -> bank_account_number )
	    g_free ( account -> bank_account_number );
    if ( account -> bank_account_key )
	    g_free ( account -> bank_account_key );
    if ( account -> bank_account_iban )
	    g_free ( account -> bank_account_iban );
    if ( account -> sort_list )
        g_slist_free( account -> sort_list ) ;
    if ( account -> form_organization )
        g_free ( account -> form_organization );
    if ( account -> bet_start_date )
        g_date_free ( account -> bet_start_date );
    if ( account -> pixbuf )
        g_object_unref ( account -> pixbuf );
    g_free ( account );
    if ( account_buffer == account )
        account_buffer = NULL;
}
