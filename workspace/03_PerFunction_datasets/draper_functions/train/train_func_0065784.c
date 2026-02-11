finish_get_engine_async (GObject *source_object,
                         GAsyncResult *res,
                         gpointer user_data)
{
    IBusInputContext *context = IBUS_INPUT_CONTEXT (source_object);
    GError *error = NULL;
    IBusEngineDesc *desc = ibus_input_context_get_engine_async_finish (context,
                                                                       res,
                                                                       &error);
    if (desc) {
        g_object_unref (desc);
    }
    g_debug ("ibus_context_get_engine_async_finish: OK");
    call_next_async_function (context);
}
