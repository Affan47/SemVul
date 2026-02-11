gsb_data_account_move_account ( gint account_number,
                        gint dest_account_number )
{
    struct_account *account;

    account = gsb_data_account_get_structure ( account_number );

    if (!account )
	return FALSE;


    list_accounts = g_slist_remove ( list_accounts,
				     account );

    if (dest_account_number != -1)
    {
	GSList *tmp_list;

	tmp_list = list_accounts;
	while ( tmp_list )
	{
	    struct_account *account_tmp;

	    account_tmp = tmp_list -> data;

	    if (account_tmp -> account_number == dest_account_number)
	    {
		list_accounts = g_slist_insert_before ( list_accounts,
							tmp_list,
							account );
		return FALSE;
	    }
	    tmp_list = tmp_list -> next;
	}
    }


    list_accounts = g_slist_append ( list_accounts,
				     account );

    return FALSE;
}
