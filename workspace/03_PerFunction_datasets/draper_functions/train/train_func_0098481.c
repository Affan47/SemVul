bluetooth_uuid_to_string (const char *uuid)
{
	char **parts;
	guint uuid16;
	gboolean is_custom = FALSE;

	if (g_str_has_suffix (uuid, "-0000-1000-8000-0002ee000002") != FALSE)
		is_custom = TRUE;

	parts = g_strsplit (uuid, "-", -1);
	if (parts == NULL || parts[0] == NULL) {
		g_strfreev (parts);
		return NULL;
	}

	uuid16 = g_ascii_strtoull (parts[0], NULL, 16);
	g_strfreev (parts);
	if (uuid16 == 0)
		return NULL;

	if (is_custom == FALSE)
		return uuid16_to_string (uuid16, uuid);
	return uuid16_custom_to_string (uuid16, uuid);
}
