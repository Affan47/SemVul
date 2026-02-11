load_all_budgets( GncSqlBackend* be )
{
    GncSqlStatement* stmt;
    GncSqlResult* result;
    GList* list = NULL;

    g_return_if_fail( be != NULL );

    stmt = gnc_sql_create_select_statement( be, BUDGET_TABLE );
    if ( stmt != NULL )
    {
        result = gnc_sql_execute_select_statement( be, stmt );
        gnc_sql_statement_dispose( stmt );
        if ( result != NULL )
        {
            GncSqlRow* row = gnc_sql_result_get_first_row( result );
            GncBudget* b;

            while ( row != NULL )
            {
                b = load_single_budget( be, row );
                if ( b != NULL )
                {
                    list = g_list_prepend( list, b );
                }
                row = gnc_sql_result_get_next_row( result );
            }
            gnc_sql_result_dispose( result );

            if ( list != NULL )
            {
                gnc_sql_slots_load_for_list( be, list );
                g_list_free( list );
            }
        }
    }
}
