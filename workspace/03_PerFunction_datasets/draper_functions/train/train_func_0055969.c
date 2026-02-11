audit_exit (GvaProcess *process,
            gint status,
            GvaAuditData *data)
{
        gchar *sql;
        GError *error = NULL;

        if (process->error != NULL)
                return;

        gva_db_transaction_begin (&error);
        gva_error_handle (&error);

        sql = g_strdup_printf ("UPDATE game SET %s=NULL", data->column);
        gva_db_execute (sql, &error);
        gva_error_handle (&error);
        g_free (sql);

        g_hash_table_foreach (
                data->status_index, (GHFunc) audit_exit_foreach, data);

        gva_db_transaction_commit (&error);
        gva_error_handle (&error);
}
