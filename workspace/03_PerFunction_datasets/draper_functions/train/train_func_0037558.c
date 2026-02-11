test_global_engine (void)
{
    GlobalEngineChangedData data;
    guint handler_id, timeout_id, idle_id;

    if (!ibus_bus_get_use_global_engine (bus))
        return;

    data.count = 0;

    handler_id = g_signal_connect (bus,
                                   "global-engine-changed",
                                   G_CALLBACK (global_engine_changed_cb),
                                   &data);
    timeout_id = g_timeout_add_seconds (1, timeout_cb, &data);
    idle_id = g_idle_add ((GSourceFunc) change_global_engine_cb, NULL);

    ibus_main ();

    g_assert_cmpint (data.count, ==, G_N_ELEMENTS (engine_names));

    g_source_remove (idle_id);
    g_source_remove (timeout_id);
    g_signal_handler_disconnect (bus, handler_id);
}
