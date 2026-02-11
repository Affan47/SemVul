gnc_sql_do_db_operation( GncSqlBackend* be,
                         E_DB_OPERATION op,
                         const gchar* table_name,
                         QofIdTypeConst obj_name, gpointer pObject,
                         const GncSqlColumnTableEntry* table )
{
    GncSqlStatement* stmt = NULL;
    gboolean ok = FALSE;

    g_return_val_if_fail( be != NULL, FALSE );
    g_return_val_if_fail( table_name != NULL, FALSE );
    g_return_val_if_fail( obj_name != NULL, FALSE );
    g_return_val_if_fail( pObject != NULL, FALSE );
    g_return_val_if_fail( table != NULL, FALSE );

    if ( op == OP_DB_INSERT )
    {
        stmt = build_insert_statement( be, table_name, obj_name, pObject, table );
    }
    else if ( op == OP_DB_UPDATE )
    {
        stmt = build_update_statement( be, table_name, obj_name, pObject, table );
    }
    else if ( op == OP_DB_DELETE )
    {
        stmt = build_delete_statement( be, table_name, obj_name, pObject, table );
    }
    else
    {
        g_assert( FALSE );
    }
    if ( stmt != NULL )
    {
        gint result;

        result = gnc_sql_connection_execute_nonselect_statement( be->conn, stmt );
        if ( result == -1 )
        {
            PERR( "SQL error: %s\n", gnc_sql_statement_to_sql( stmt ) );
            qof_backend_set_error( &be->be, ERR_BACKEND_SERVER_ERR );
        }
        else
        {
            ok = TRUE;
        }
        gnc_sql_statement_dispose( stmt );
    }

    return ok;
}
