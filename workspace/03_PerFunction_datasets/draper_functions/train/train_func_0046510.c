get_publisher_policy_info (MonoImage *image, MonoAssemblyName *aname, MonoAssemblyBindingInfo *binding_info)
{
	MonoTableInfo *t;
	guint32 cols [MONO_MANIFEST_SIZE];
	const gchar *filename;
	gchar *subpath, *fullpath;

	t = &image->tables [MONO_TABLE_MANIFESTRESOURCE];


	if (t->rows < 1) {
		binding_info->is_valid = FALSE;
		return;
	}

	mono_metadata_decode_row (t, 0, cols, MONO_MANIFEST_SIZE);
	if ((cols [MONO_MANIFEST_IMPLEMENTATION] & MONO_IMPLEMENTATION_MASK) != MONO_IMPLEMENTATION_FILE) {
		binding_info->is_valid = FALSE;
		return;
	}

	filename = mono_metadata_string_heap (image, cols [MONO_MANIFEST_NAME]);
	g_assert (filename != NULL);

	subpath = g_path_get_dirname (image->name);
	fullpath = g_build_path (G_DIR_SEPARATOR_S, subpath, filename, NULL);
	mono_config_parse_publisher_policy (fullpath, binding_info);
	g_free (subpath);
	g_free (fullpath);


	if (!binding_info->culture)
		binding_info->culture = g_strdup ("");


	if (!binding_info->name || !binding_info->public_key_token [0] || !binding_info->has_old_version_bottom ||
			!binding_info->has_new_version || !assembly_binding_maps_name (binding_info, aname)) {
		mono_assembly_binding_info_free (binding_info);
		binding_info->is_valid = FALSE;
		return;
	}

	binding_info->is_valid = TRUE;
}
