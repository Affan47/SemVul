nautilus_file_get_parent_uri_for_display (NautilusFile *file)
{
	GFile *parent;
	char *result;

	g_assert (NAUTILUS_IS_FILE (file));

	parent = nautilus_file_get_parent_location (file);
	if (parent) {
		result = g_file_get_parse_name (parent);
		g_object_unref (parent);
	} else {
		result = g_strdup ("");
	}

	return result;
}
