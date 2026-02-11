settings_is_unique_instance(void)
{
	g_assert(config_dir);

	return settings_unique_usage(config_dir, pidfile, NULL) && EEXIST == errno;
}
