query_callback (SoupSession *session,
                SoupMessage *query,
                gpointer     user_data)
{
        QueryCallbackData *data = (QueryCallbackData *) user_data;
        GSimpleAsyncResult *simple = data->simple;
        GError *error = NULL;
        char *contents;

        if (data->cancellable != NULL)
                g_signal_handler_disconnect (data->cancellable,
                                             data->cancelled_id);

        if (query->status_code != SOUP_STATUS_OK) {
                GIOErrorEnum code;

                if (query->status_code == SOUP_STATUS_CANCELLED)
                        code = G_IO_ERROR_CANCELLED;
                else
                        code = G_IO_ERROR_FAILED;
		g_set_error_literal (&error, G_IO_ERROR, code,
                                     query->reason_phrase ? query->reason_phrase : "Query failed");
                g_simple_async_result_take_error (simple, error);
		g_simple_async_result_complete (simple);
		query_callback_data_free (data);
		return;
	}

        contents = g_strndup (query->response_body->data, query->response_body->length);
        g_simple_async_result_set_op_res_gpointer (simple, contents, NULL);

        g_simple_async_result_complete (simple);
        query_callback_data_free (data);
}
