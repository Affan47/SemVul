gsb_data_archive_remove ( gint archive_number )
{
    struct_archive *archive;
    GSList *tmp_list;

    archive = gsb_data_archive_get_structure ( archive_number );

    if (!archive)
	return FALSE;


    tmp_list = gsb_data_transaction_get_complete_transactions_list ();
    while (tmp_list)
    {
	gint transaction_number;

	transaction_number = gsb_data_transaction_get_transaction_number (tmp_list -> data);
	if (gsb_data_transaction_get_archive_number (transaction_number) == archive -> archive_number)
	    gsb_data_transaction_set_archive_number ( transaction_number,
						      0 );
	tmp_list = tmp_list -> next;
    }


    archive_list = g_slist_remove ( archive_list,
				    archive );

    _gsb_data_archive_free (archive);

    return TRUE;
}
