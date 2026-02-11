finish_get_prop_global_engine_async (GObject *source_object,
                                     GAsyncResult *res,
                                     gpointer user_data)
{
    GError *error = NULL;
    GVariant *result, *obj;
    IBusEngineDesc *desc = NULL;

    result = ibus_bus_get_ibus_property_async_finish (bus, res, &error);
    obj = g_variant_get_variant (result);
    desc = IBUS_ENGINE_DESC (ibus_serializable_deserialize (obj));
    g_variant_unref (obj);
    g_variant_unref (result);

    if (desc)
        g_object_unref (desc);

    g_debug ("finish_get_prop_global_engine_async: OK");
    call_next_async_function ();
}
