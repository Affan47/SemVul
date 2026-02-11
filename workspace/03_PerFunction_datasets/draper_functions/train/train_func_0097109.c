set_ipv6_method(const char *method)
{
	gboolean privacy_enabled = FALSE;

	if (g_strcmp0(method, "auto") == 0) {
		toggle_button("ipv6_auto");
		enable_ipv6_config(FALSE);

		privacy_enabled = TRUE;
	} else if (g_strcmp0(method, "manual") == 0) {
		toggle_button("ipv6_manual");
		enable_ipv6_config(TRUE);
	} else {
		toggle_button("ipv6_off");
		enable_ipv6_config(FALSE);
	}

	set_widget_sensitive(builder, "ipv6_priv_box", privacy_enabled);
}
