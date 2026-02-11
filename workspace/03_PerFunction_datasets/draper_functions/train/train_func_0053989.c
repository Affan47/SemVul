plugin_failed (NMDnsPlugin *plugin, gpointer user_data)
{
	NMDnsManager *self = NM_DNS_MANAGER (user_data);
	GError *error = NULL;


	if (!nm_dns_plugin_is_caching (plugin))
		return;


	if (!update_dns (self, TRUE, &error)) {
		nm_log_warn (LOGD_DNS, "could not commit DNS changes: (%d) %s",
		             error ? error->code : -1,
		             error && error->message ? error->message : "(unknown)");
		g_clear_error (&error);
	}
}
