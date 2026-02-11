db_parser_exit (GvaProcess *process,
                gint status,
                ParserData *data)
{
        GError *error = NULL;

        if (process->error == NULL)
        {
                GTimeVal time_elapsed;

                g_markup_parse_context_end_parse (
                        data->context, &process->error);

                gva_db_transaction_commit (&error);
                gva_error_handle (&error);

                gva_process_get_time_elapsed (process, &time_elapsed);

                g_message (
                        "Database built in %ld.%ld seconds.",
                        time_elapsed.tv_sec, time_elapsed.tv_usec / 100000);
        }
        else
        {
                gva_db_transaction_rollback (&error);
                gva_error_handle (&error);
        }

        db_parser_data_free (data);
}
