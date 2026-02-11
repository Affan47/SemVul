gclue_ipclient_search_async (GClueIpclient      *ipclient,
                             GCancellable       *cancellable,
                             GAsyncReadyCallback callback,
                             gpointer            user_data)
{
        QueryCallbackData *data;

        g_return_if_fail (GCLUE_IS_IPCLIENT (ipclient));

        data = g_slice_new0 (QueryCallbackData);
        data->simple = g_simple_async_result_new (g_object_ref (ipclient),
                                                  callback,
                                                  user_data,
                                                  gclue_ipclient_search_async);
        if (cancellable != NULL)
                data->cancellable = g_object_ref (cancellable);
        data->message = get_search_query (ipclient);

        if (cancellable != NULL)
                data->cancelled_id = g_signal_connect
                        (cancellable,
                         "cancelled",
                         G_CALLBACK (search_cancelled_callback),
                         data);
        soup_session_queue_message (ipclient->priv->soup_session,
                                    data->message,
                                    query_callback,
                                    data);
}
