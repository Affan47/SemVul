resolv_result(GResolvResultStatus status,
					char **results, gpointer user_data)
{
	struct vpn_provider *provider = user_data;

	DBG("status %d", status);

	if (status == G_RESOLV_RESULT_STATUS_SUCCESS && results != NULL &&
						g_strv_length(results) > 0)
		provider->host_ip = g_strdupv(results);

	vpn_provider_unref(provider);
}
