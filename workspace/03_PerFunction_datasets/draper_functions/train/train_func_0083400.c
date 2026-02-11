show_wireless_dialog (CcNetworkPanel   *panel,
		      NMClient         *client,
		      NMRemoteSettings *settings,
		      GtkWidget        *dialog)
{
        GtkWidget *toplevel = cc_shell_get_toplevel (cc_panel_get_shell (CC_PANEL (panel)));
        WirelessDialogClosure *closure;

        g_debug ("About to parent and show a network dialog");

        g_assert (gtk_widget_is_toplevel (toplevel));
        g_object_set (G_OBJECT (dialog),
                      "modal", TRUE,
                      "transient-for", toplevel,
                      NULL);

        closure = g_slice_new (WirelessDialogClosure);
        closure->client = g_object_ref (client);
        closure->settings = g_object_ref (settings);
        g_signal_connect_data (dialog, "response",
                               G_CALLBACK (wireless_dialog_response_cb),
                               closure, wireless_dialog_closure_closure_notify, 0);

        g_object_bind_property (G_OBJECT (toplevel), "visible",
                                G_OBJECT (dialog), "visible",
                                G_BINDING_SYNC_CREATE);
}
