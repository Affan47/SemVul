_async_finish_object_path (GAsyncResult *res,
                           GError      **error)
{
    GSimpleAsyncResult *simple = (GSimpleAsyncResult *) res;
    if (g_simple_async_result_propagate_error (simple, error))
        return NULL;
    GVariant *result = g_simple_async_result_get_op_res_gpointer (simple);
    GVariant *variant = NULL;
    g_return_val_if_fail (result != NULL, NULL);
    gchar *path = NULL;
    g_variant_get (result, "(v)", &variant);
    path = g_variant_dup_string (variant, NULL);
    g_variant_unref (variant);
    return path;
}
