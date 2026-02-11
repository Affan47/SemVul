cc_network_panel_notify_enable_active_cb (GtkSwitch *sw,
                                          GParamSpec *pspec,
                                          CcNetworkPanel *panel)
{
	gboolean enable;
	struct rfkill_event event;

	enable = gtk_switch_get_active (sw);
	g_debug ("Setting killswitch to %d", enable);

	memset (&event, 0, sizeof(event));
	event.op = RFKILL_OP_CHANGE_ALL;
	event.type = RFKILL_TYPE_ALL;
	event.soft = enable ? 1 : 0;
	if (cc_rfkill_glib_send_event (panel->priv->rfkill, &event) < 0)
		g_warning ("Setting the killswitch %s failed", enable ? "on" : "off");
}
