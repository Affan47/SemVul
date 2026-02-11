_g_key_file_get_rgba (GKeyFile  *key_file,
		      char      *group_name,
		      char      *key,
		      GdkRGBA   *color,
		      GError   **error)
{
	char *spec;

	spec = g_key_file_get_string (key_file, group_name, key, error);
	if (spec != NULL)
		gdk_rgba_parse (color, spec);

	g_free (spec);
}
