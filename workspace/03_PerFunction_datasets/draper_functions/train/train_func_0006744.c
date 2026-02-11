create_finish_success (GObject      *object,
                       GAsyncResult *res,
                       gpointer      user_data)
{
    g_assert (object == (GObject *)bus);
    g_assert (user_data == NULL);

    GError *error = NULL;
    IBusInputContext *context = NULL;
    context = ibus_bus_create_input_context_async_finish (bus, res, &error);

    g_assert (IBUS_IS_INPUT_CONTEXT (context));
    g_object_unref (context);
    ibus_quit ();
}
