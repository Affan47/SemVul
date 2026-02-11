midgard_core_config_build_schemadir_path (const gchar *dirname)
{
	gchar *lschema_dir = NULL;

	if (dirname != NULL && *dirname == '\0') {

		g_warning("Empty directory given to read schema files from. Use explicit NULL for system defaults.");
		return NULL;
	}

	if (dirname != NULL)
		lschema_dir = g_build_path(G_DIR_SEPARATOR_S, dirname, MIDGARD_CONFIG_RW_SCHEMA, NULL);

	if (lschema_dir == NULL) {

		const gchar *env_sharedir = g_getenv("MIDGARD_ENV_GLOBAL_SHAREDIR");

		if (env_sharedir != NULL && *env_sharedir != '\0') {

			lschema_dir = g_build_path(G_DIR_SEPARATOR_S, env_sharedir, MIDGARD_CONFIG_RW_SCHEMA, NULL);

		} else {

			lschema_dir = g_build_path(G_DIR_SEPARATOR_S,
					MIDGARD_LIB_PREFIX, "share", MIDGARD_PACKAGE_NAME, MIDGARD_CONFIG_RW_SCHEMA, NULL);
  		}
	}

	if (!g_file_test (lschema_dir, G_FILE_TEST_IS_DIR)) {

		g_warning("%s doesn't seem to be schema directory", lschema_dir);

		if (lschema_dir)
			g_free(lschema_dir);

		return NULL;
	}

	return lschema_dir;
}
