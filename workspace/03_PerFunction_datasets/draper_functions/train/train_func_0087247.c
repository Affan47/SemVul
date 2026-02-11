_init_ibus (void)
{
    if (_bus != NULL)
        return;

    ibus_init ();

    _bus = ibus_bus_new ();

    g_signal_connect (_bus, "disconnected",
                        G_CALLBACK (_bus_disconnected_cb), NULL);

    _use_sync_mode = _get_boolean_env ("IBUS_ENABLE_SYNC_MODE", FALSE);
}
