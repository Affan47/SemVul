vpn_provider_new(void)
{
	struct vpn_provider *provider;

	provider = g_try_new0(struct vpn_provider, 1);
	if (provider == NULL)
		return NULL;

	provider->refcount = 1;

	DBG("provider %p", provider);
	provider_initialize(provider);

	return provider;
}
