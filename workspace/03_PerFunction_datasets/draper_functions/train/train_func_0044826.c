load_recurrence( GncSqlBackend* be, GncSqlRow* row,  Recurrence* r )
{
    recurrence_info_t recurrence_info;

    g_return_if_fail( be != NULL );
    g_return_if_fail( row != NULL );
    g_return_if_fail( r != NULL );

    recurrence_info.be = be;
    recurrence_info.pRecurrence = r;

    gnc_sql_load_object( be, row, TABLE_NAME, &recurrence_info, col_table );
}
