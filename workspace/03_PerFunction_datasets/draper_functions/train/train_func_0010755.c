gclue_ipclient_search_finish (GClueIpclient *ipclient,
                              GAsyncResult  *res,
                              GError       **error)
{
        GSimpleAsyncResult *simple = G_SIMPLE_ASYNC_RESULT (res);
        char *contents = NULL;
        GeocodeLocation *location;

        g_return_val_if_fail (GCLUE_IS_IPCLIENT (ipclient), NULL);

        g_warn_if_fail (g_simple_async_result_get_source_tag (simple) == gclue_ipclient_search_async);

        if (g_simple_async_result_propagate_error (simple, error))
                return NULL;

        contents = g_simple_async_result_get_op_res_gpointer (simple);
        location = _gclue_ip_json_to_location (contents, error);
        g_free (contents);
        g_object_unref (ipclient);

        return location;
}
