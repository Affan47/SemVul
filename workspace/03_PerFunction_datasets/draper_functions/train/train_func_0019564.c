create_recurrence_tables( GncSqlBackend* be )
{
    gint version;
    gboolean ok;

    g_return_if_fail( be != NULL );

    version = gnc_sql_get_table_version( be, TABLE_NAME );
    if ( version == 0 )
    {
        (void)gnc_sql_create_table( be, TABLE_NAME, TABLE_VERSION, col_table );
    }
    else if ( version < TABLE_VERSION )
    {


        if ( version == 1 )
        {
            upgrade_recurrence_table_1_2 (be);
        }
        (void)gnc_sql_set_table_version( be, TABLE_NAME, TABLE_VERSION );
        PINFO("Recurrence table upgraded from version %d to version %d\n", version, TABLE_VERSION);
    }
}
