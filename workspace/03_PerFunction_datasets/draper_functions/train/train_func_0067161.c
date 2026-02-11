bus_test_client_class_init (BusTestClientClass *class)
{
    IDEBUG ("%s", __FUNCTION__);

    IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (class);

    ibus_object_class->destroy = bus_test_client_destroy;


    if (_xdisplay == NULL) {
        _xdisplay = XOpenDisplay (NULL);
    }


    if (_bus == NULL) {
        ibus_set_display (XDisplayString (_xdisplay));
        _bus = ibus_bus_new();
    }

    g_signal_connect (_bus, "disconnected", G_CALLBACK (_bus_disconnected_cb), NULL);
}
