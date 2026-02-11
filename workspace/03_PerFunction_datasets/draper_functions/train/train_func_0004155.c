module_create (char const *name)
{
	char		*module_path;
	ccss_cairo_appearance_module_t	*module = NULL;

	if (NULL == _module_hash) {
		_module_hash = g_hash_table_new (g_str_hash, g_str_equal);
	}

	module_path = g_module_build_path (CCSS_CAIRO_APPEARANCE_MODULE_PATH,
					   name);


	module = g_hash_table_lookup (_module_hash, module_path);
	if (module) {

		module->reference_count++;

	} else {

		GModule *gmodule = g_module_open (module_path,
						  G_MODULE_BIND_LAZY | G_MODULE_BIND_LOCAL);
		if (gmodule) {

			ccss_appearance_module_get_interface_version get_version = NULL;
			bool ret = g_module_symbol (gmodule,
						    "ccss_appearance_module_get_interface_version",
						    (gpointer *) &get_version);
			if (ret && get_version) {
				char const *version = get_version ();
				if (0 == g_strcmp0 (version, CCSS_CAIRO_APPEARANCE_MODULE_INTERFACE_VERSION)) {
					module = g_new0 (ccss_cairo_appearance_module_t, 1);
					module->reference_count = 1;
					module->module_path = g_strdup (module_path);
					module->module = gmodule;
				} else {
					g_debug ("%s : skipping module '%s' with version '%s' (require '%s')",
						 G_STRLOC,
						 module_path,
						 version,
						 CCSS_CAIRO_APPEARANCE_MODULE_INTERFACE_VERSION);
				}
			} else {
				g_critical ("%s : failed to look up symbol '%s' of module '%s'",
					    G_STRLOC,
					    "ccss_appearance_module_get_interface_version",
					    module_path);
			}
		} else {
			g_critical ("%s : could not open module '%s'",
				    G_STRLOC,
				    module_path);
		}


		if (module) {

			g_hash_table_insert (_module_hash,
					     module->module_path,
					     module);
		}
	}
	g_free (module_path), module_path = NULL;

	return module;
}
