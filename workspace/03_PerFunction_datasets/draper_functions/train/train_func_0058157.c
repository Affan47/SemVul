gnc_sql_save_transaction( GncSqlBackend* be, QofInstance* inst )
{
    g_return_val_if_fail( be != NULL, FALSE );
    g_return_val_if_fail( inst != NULL, FALSE );
    g_return_val_if_fail( GNC_IS_TRANS(inst), FALSE );

    return save_transaction( be, GNC_TRANS(inst), TRUE );
}
