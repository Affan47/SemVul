gsb_data_account_sort_list_add ( gint account_number,
                        gint payment_number )
{
    struct_account *account;

    account = gsb_data_account_get_structure ( account_number );

    if (!account )
	return FALSE;

    account -> sort_list = g_slist_append ( account -> sort_list,
					    GINT_TO_POINTER (payment_number));

    return TRUE;
}
