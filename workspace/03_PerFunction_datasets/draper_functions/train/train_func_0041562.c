ibus_input_context_get_engine_async (IBusInputContext   *context,
                                     gint                timeout_msec,
                                     GCancellable       *cancellable,
                                     GAsyncReadyCallback callback,
                                     gpointer            user_data)
{
    g_assert (IBUS_IS_INPUT_CONTEXT (context));
    g_dbus_proxy_call ((GDBusProxy *) context,
                       "GetEngine",
                       NULL,
                       G_DBUS_CALL_FLAGS_NONE,
                       timeout_msec,
                       cancellable,
                       callback,
                       user_data);
}
