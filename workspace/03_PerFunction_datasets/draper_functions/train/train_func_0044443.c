cc_network_panel_connect_to_3g_network (CcNetworkPanel   *panel,
                                        NMClient         *client,
                                        NMRemoteSettings *settings,
                                        NMDevice         *device)
{
        GtkWidget *toplevel = cc_shell_get_toplevel (cc_panel_get_shell (CC_PANEL (panel)));
        MobileDialogClosure *closure;
        NMAMobileWizard *wizard;
	NMDeviceModemCapabilities caps;
        gboolean visible = FALSE;

        g_debug ("connect to 3g");
        if (!NM_IS_DEVICE_MODEM (device)) {
                g_warning ("Network panel loaded with connect-3g but the selected device"
                           " is not a modem");
                return;
        }

        closure = g_slice_new (MobileDialogClosure);
        closure->client = g_object_ref (client);
        closure->settings = g_object_ref (settings);
        closure->device = g_object_ref (device);

	caps = nm_device_modem_get_current_capabilities (NM_DEVICE_MODEM (device));
	if (caps & NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS) {
                wizard = nma_mobile_wizard_new (GTK_WINDOW (toplevel), NULL, NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS, FALSE,
                                                gsm_mobile_wizard_done, closure);
		if (wizard == NULL) {
			g_warning ("failed to construct GSM wizard");
			return;
		}
	} else if (caps & NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO) {
		wizard = nma_mobile_wizard_new (GTK_WINDOW (toplevel), NULL, NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO, FALSE,
                                                cdma_mobile_wizard_done, closure);
		if (wizard == NULL) {
			g_warning ("failed to construct CDMA wizard");
			return;
		}
        } else {
                g_warning ("Network panel loaded with connect-3g but the selected device"
                           " does not support GSM or CDMA");
                mobile_dialog_closure_free (closure);
                return;
        }

        g_object_get (G_OBJECT (toplevel), "visible", &visible, NULL);
        if (visible) {
                g_debug ("Scheduling showing the Mobile wizard");
                g_idle_add ((GSourceFunc) show_wizard_idle_cb, wizard);
        } else {
                g_debug ("Will show wizard a bit later, toplevel is not visible");
                g_signal_connect (G_OBJECT (toplevel), "notify::visible",
                                  G_CALLBACK (toplevel_shown), wizard);
        }
}
