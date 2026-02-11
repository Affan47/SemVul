load_single_account( GncSqlBackend* be, GncSqlRow* row,
                     GList** l_accounts_needing_parents )
{
    const GncGUID* guid;
    Account* pAccount = NULL;

    g_return_val_if_fail( be != NULL, NULL );
    g_return_val_if_fail( row != NULL, NULL );
    g_return_val_if_fail( l_accounts_needing_parents != NULL, NULL );

    guid = gnc_sql_load_guid( be, row );
    if ( guid != NULL )
    {
        pAccount = xaccAccountLookup( guid, be->book );
    }
    if ( pAccount == NULL )
    {
        pAccount = xaccMallocAccount( be->book );
    }
    xaccAccountBeginEdit( pAccount );
    gnc_sql_load_object( be, row, GNC_ID_ACCOUNT, pAccount, col_table );
    xaccAccountCommitEdit( pAccount );


    if ( gnc_account_get_parent( pAccount ) == NULL
            && pAccount != gnc_book_get_root_account( be->book ) )
    {
        account_parent_guid_struct* s = g_malloc( (gsize)sizeof(account_parent_guid_struct) );
        g_assert( s != NULL );

        s->pAccount = pAccount;
        gnc_sql_load_object( be, row, GNC_ID_ACCOUNT, s, parent_col_table );
        *l_accounts_needing_parents = g_list_prepend( *l_accounts_needing_parents, s );
    }

    return pAccount;
}
