_dbus_powered_GetDevice (Powered* self, const char* purpose, char** url, GError** error) {
	powered_GetDevice (self, purpose, url, error);
	return !error || !*error;
}
