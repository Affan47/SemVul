disabled_timeout_callback (void)
{
	http_down ();

	if (g_settings_get_boolean (settings, FILE_SHARING_BLUETOOTH_ENABLED) == FALSE &&
	    g_settings_get_boolean (settings, FILE_SHARING_BLUETOOTH_OBEXPUSH_ENABLED) == FALSE)
		_exit (0);
	return FALSE;
}
