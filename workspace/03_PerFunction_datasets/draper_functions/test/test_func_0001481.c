osinfo_install_script_generate_finish_common(OsinfoInstallScript *script,
                                                             GAsyncResult *res,
                                                             GError **error)
{
    GSimpleAsyncResult *simple = G_SIMPLE_ASYNC_RESULT(res);

    g_return_val_if_fail(error == NULL || *error == NULL, NULL);

    if (g_simple_async_result_propagate_error(simple, error))
        return NULL;

    return g_simple_async_result_get_op_res_gpointer(simple);
}
