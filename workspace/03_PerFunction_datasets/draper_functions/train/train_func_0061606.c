nm_dns_plugin_get_name (NMDnsPlugin *self)
{
	g_assert (NM_DNS_PLUGIN_GET_CLASS (self)->get_name);
	return NM_DNS_PLUGIN_GET_CLASS (self)->get_name (self);
}
