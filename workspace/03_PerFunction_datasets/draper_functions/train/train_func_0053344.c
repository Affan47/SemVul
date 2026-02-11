pk_engine_daemon_get_property (GDBusConnection *connection_, const gchar *sender,
			       const gchar *object_path, const gchar *interface_name,
			       const gchar *property_name, GError **error,
			       gpointer user_data)
{
	GVariant *retval = NULL;
	PkEngine *engine = PK_ENGINE (user_data);


	pk_engine_reset_timer (engine);

	if (g_strcmp0 (property_name, "VersionMajor") == 0) {
		retval = g_variant_new_uint32 (PK_MAJOR_VERSION);
		goto out;
	}
	if (g_strcmp0 (property_name, "VersionMinor") == 0) {
		retval = g_variant_new_uint32 (PK_MINOR_VERSION);
		goto out;
	}
	if (g_strcmp0 (property_name, "VersionMicro") == 0) {
		retval = g_variant_new_uint32 (PK_MICRO_VERSION);
		goto out;
	}
	if (g_strcmp0 (property_name, "BackendName") == 0) {
		retval = g_variant_new_string (engine->priv->backend_name);
		goto out;
	}
	if (g_strcmp0 (property_name, "BackendDescription") == 0) {
		retval = _g_variant_new_maybe_string (engine->priv->backend_description);
		goto out;
	}
	if (g_strcmp0 (property_name, "BackendAuthor") == 0) {
		retval = _g_variant_new_maybe_string (engine->priv->backend_author);
		goto out;
	}
	if (g_strcmp0 (property_name, "Roles") == 0) {
		retval = g_variant_new_uint64 (engine->priv->roles);
		goto out;
	}
	if (g_strcmp0 (property_name, "Provides") == 0) {
		retval = g_variant_new_uint64 (engine->priv->provides);
		goto out;
	}
	if (g_strcmp0 (property_name, "Groups") == 0) {
		retval = g_variant_new_uint64 (engine->priv->groups);
		goto out;
	}
	if (g_strcmp0 (property_name, "Filters") == 0) {
		retval = g_variant_new_uint64 (engine->priv->filters);
		goto out;
	}
	if (g_strcmp0 (property_name, "MimeTypes") == 0) {
		retval = g_variant_new_strv ((const gchar * const *) engine->priv->mime_types, -1);
		goto out;
	}
	if (g_strcmp0 (property_name, "Locked") == 0) {
		retval = g_variant_new_boolean (engine->priv->locked);
		goto out;
	}
	if (g_strcmp0 (property_name, "NetworkState") == 0) {
		retval = g_variant_new_uint32 (engine->priv->network_state);
		goto out;
	}
	if (g_strcmp0 (property_name, "DistroId") == 0) {
		retval = _g_variant_new_maybe_string (engine->priv->distro_id);
		goto out;
	}


	g_set_error (error,
		     PK_ENGINE_ERROR,
		     PK_ENGINE_ERROR_NOT_SUPPORTED,
		     "failed to get property '%s'",
		     property_name);
out:
	return retval;
}
