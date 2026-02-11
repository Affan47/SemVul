load_single_billterm( GncSqlBackend* be, GncSqlRow* row,
                      GList** l_billterms_needing_parents )
{
    const GncGUID* guid;
    GncBillTerm* pBillTerm;

    g_return_val_if_fail( be != NULL, NULL );
    g_return_val_if_fail( row != NULL, NULL );

    guid = gnc_sql_load_guid( be, row );
    pBillTerm = gncBillTermLookup( be->book, guid );
    if ( pBillTerm == NULL )
    {
        pBillTerm = gncBillTermCreate( be->book );
    }
    gnc_sql_load_object( be, row, GNC_ID_BILLTERM, pBillTerm, col_table );


    if ( gncBillTermGetParent( pBillTerm ) == NULL )
    {
        billterm_parent_guid_struct* s = g_malloc( (gsize)sizeof(billterm_parent_guid_struct) );
        g_assert( s != NULL );

        s->billterm = pBillTerm;
        s->have_guid = FALSE;
        gnc_sql_load_object( be, row, GNC_ID_TAXTABLE, s, billterm_parent_col_table );
        if ( s->have_guid )
        {
            *l_billterms_needing_parents = g_list_prepend( *l_billterms_needing_parents, s );
        }
        else
        {
            g_free( s );
        }
    }

    qof_instance_mark_clean( QOF_INSTANCE(pBillTerm) );

    return pBillTerm;
}
