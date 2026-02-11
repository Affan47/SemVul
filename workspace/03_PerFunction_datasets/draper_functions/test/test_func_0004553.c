save_budget_amounts( GncSqlBackend* be, GncBudget* budget )
{
    GList* descendants;

    GList* node;
    budget_amount_info_t info;
    guint num_periods;
    gboolean is_ok = TRUE;;

    g_return_val_if_fail( be != NULL, FALSE );
    g_return_val_if_fail( budget != NULL, FALSE );


    delete_budget_amounts( be, budget );

    info.budget = budget;
    num_periods = gnc_budget_get_num_periods( budget );
    descendants = gnc_account_get_descendants( gnc_book_get_root_account( be->book ) );
    for ( node = descendants; node != NULL && is_ok; node = g_list_next(node) )
    {
        guint i;

        info.account = GNC_ACCOUNT(node->data);
        for ( i = 0; i < num_periods && is_ok; i++ )
        {
            if ( gnc_budget_is_account_period_value_set( budget, info.account, i ) )
            {
                info.period_num = i;
                is_ok = gnc_sql_do_db_operation( be, OP_DB_INSERT, AMOUNTS_TABLE, "", &info,
                                                 budget_amounts_col_table );
            }
        }
    }
    g_list_free( descendants );

    return is_ok;
}
