switch_hotspot_changed_cb (GtkSwitch *sw,
                           GParamSpec *pspec,
                           NetDeviceWifi *device_wifi)
{
        GtkWidget *dialog;
        GtkWidget *window;
        CcNetworkPanel *panel;

        if (device_wifi->priv->updating_device)
                return;

        panel = net_object_get_panel (NET_OBJECT (device_wifi));
        window = gtk_widget_get_toplevel (GTK_WIDGET (panel));
        dialog = gtk_message_dialog_new (GTK_WINDOW (window),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_OTHER,
                                         GTK_BUTTONS_NONE,
                                         _("Stop hotspot and disconnect any users?"));
        gtk_dialog_add_buttons (GTK_DIALOG (dialog),
                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                _("_Stop Hotspot"), GTK_RESPONSE_OK,
                                NULL);
        g_signal_connect (dialog, "response",
                          G_CALLBACK (stop_hotspot_response_cb), device_wifi);
        gtk_window_present (GTK_WINDOW (dialog));
}
