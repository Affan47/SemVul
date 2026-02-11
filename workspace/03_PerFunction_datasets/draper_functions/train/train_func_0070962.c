on_location_read(GObject *source,
                             GAsyncResult *res,
                             gpointer user_data)
{
    CreateFromLocationAsyncData *data;
    GError *error = NULL;
    gchar *content = NULL;
    gsize length = 0;
    OsinfoTree *ret = NULL;

    data = (CreateFromLocationAsyncData *)user_data;

    if (!g_file_load_contents_finish(G_FILE(source),
                                     res,
                                     &content,
                                     &length,
                                     NULL,
                                     &error)) {
        g_prefix_error(&error, _("Failed to load .treeinfo file: "));
        g_simple_async_result_take_error(data->res, error);
        g_simple_async_result_complete(data->res);
        create_from_location_async_data_free(data);
        return;
    }

    if (!(ret = load_keyinfo(data->location,
                             content,
                             length,
                             &error))) {
        g_prefix_error(&error, _("Failed to process keyinfo file: "));
        g_simple_async_result_take_error(data->res, error);
        goto cleanup;
    }

    g_simple_async_result_set_op_res_gpointer(data->res, ret, NULL);

 cleanup:
    g_simple_async_result_complete (data->res);
    create_from_location_async_data_free(data);
    g_free(content);
}
