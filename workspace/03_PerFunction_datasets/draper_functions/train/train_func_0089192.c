create_budget_tables( GncSqlBackend* be )
{
    gint version;

    g_return_if_fail( be != NULL );

    version = gnc_sql_get_table_version( be, BUDGET_TABLE );
    if ( version == 0 )
    {
        (void)gnc_sql_create_table( be, BUDGET_TABLE, TABLE_VERSION, col_table );
    }

    version = gnc_sql_get_table_version( be, AMOUNTS_TABLE );
    if ( version == 0 )
    {
        (void)gnc_sql_create_table( be, AMOUNTS_TABLE, AMOUNTS_TABLE_VERSION, budget_amounts_col_table );
    }
}
