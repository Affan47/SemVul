ibus_bus_get_global_engine_async_finish (IBusBus      *bus,
                                         GAsyncResult *res,
                                         GError      **error)
{
    GSimpleAsyncResult *simple = (GSimpleAsyncResult *) res;
    if (g_simple_async_result_propagate_error (simple, error))
        return NULL;
    GVariant *result = g_simple_async_result_get_op_res_gpointer (simple);
    g_return_val_if_fail (result != NULL, NULL);
    GVariant *variant = NULL;
    g_variant_get (result, "(v)", &variant);

    IBusEngineDesc *engine = NULL;
    if (variant) {
        GVariant *obj = g_variant_get_variant (variant);
        engine = IBUS_ENGINE_DESC (ibus_serializable_deserialize (obj));
        g_variant_unref (obj);
        g_variant_unref (variant);
    }
    return engine;
}
