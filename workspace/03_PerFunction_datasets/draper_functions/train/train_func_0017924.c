port_mapping_update(property_t unused_prop)
{
	static GtkWidget *icon_possible;
	static GtkWidget *icon_upnp_successful;
	static GtkWidget *icon_natpmp_successful;
	gboolean pm_successful;
	gboolean upnp, natpmp, upnp_enabled, natpmp_enabled;

	(void) unused_prop;

	if G_UNLIKELY(NULL == icon_possible) {
		icon_possible =
			gui_main_window_lookup("eventbox_port_mapping_possible");
		icon_upnp_successful =
			gui_main_window_lookup("eventbox_upnp_port_mapping_successful");
		icon_natpmp_successful =
			gui_main_window_lookup("eventbox_natpmp_port_mapping_successful");
	}

    gnet_prop_get_boolean_val(PROP_PORT_MAPPING_SUCCESSFUL, &pm_successful);
    gnet_prop_get_boolean_val(PROP_UPNP_POSSIBLE, &upnp);
    gnet_prop_get_boolean_val(PROP_NATPMP_POSSIBLE, &natpmp);
    gnet_prop_get_boolean_val(PROP_ENABLE_UPNP, &upnp_enabled);
    gnet_prop_get_boolean_val(PROP_ENABLE_NATPMP, &natpmp_enabled);

	gtk_widget_hide(icon_possible);
	gtk_widget_hide(icon_upnp_successful);
	gtk_widget_hide(icon_natpmp_successful);

	if (pm_successful) {
		if (natpmp && natpmp_enabled)
			gtk_widget_show(icon_natpmp_successful);
		else if (upnp && upnp_enabled)
			gtk_widget_show(icon_upnp_successful);
		else
			gtk_widget_show(icon_possible);
	} else if (upnp || natpmp) {
		gtk_widget_show(icon_possible);
	}

	gui_shrink_widget_named("hbox_port_mapping");

	return FALSE;
}
