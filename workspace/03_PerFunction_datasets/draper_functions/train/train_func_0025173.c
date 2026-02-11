gconfClient(void)
{
	if (!_gconfClient) {
		_gconfClient = gconf_client_get_default();
		g_assert(GCONF_IS_CLIENT(_gconfClient));
		gconf_client_add_dir(_gconfClient, PACKAGE_GCONF_DIR, GCONF_CLIENT_PRELOAD_ONELEVEL, NULL);
	}
	return _gconfClient;
}
