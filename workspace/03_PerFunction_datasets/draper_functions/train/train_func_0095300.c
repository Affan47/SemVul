provider_free(gpointer data)
{
	struct connman_provider *provider = data;

	if (provider == NULL)
		return;

	g_free(provider->host);
	g_free(provider->domain);
	g_free(provider->name);
	g_free(provider->type);

	g_free(provider);
}
