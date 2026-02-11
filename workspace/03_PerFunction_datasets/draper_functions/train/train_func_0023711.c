initialize_uris (void)
{
	GPtrArray *uris;
	GList *l;
	gchar *uri;
	gchar *debug;

	if (initialized_uris)
		return;

	if (!initialized_modules) {
		_gcr_debug ("modules not initialized");
		return;
	}

	G_LOCK (uris);

	if (!initialized_uris) {

		trust_store_uri = p11_kit_config_option (NULL, "x-trust-store");
		for (l = all_modules; !trust_store_uri && l != NULL; l = g_list_next (l)) {
			trust_store_uri = p11_kit_config_option (gck_module_get_functions (l->data),
			                                         "x-trust-store");
		}

		uris = g_ptr_array_new ();
		uri = p11_kit_config_option (NULL, "x-trust-lookup");
		if (uri != NULL)
			g_ptr_array_add (uris, uri);
		for (l = all_modules; l != NULL; l = g_list_next (l)) {
			uri = p11_kit_config_option (gck_module_get_functions (l->data),
			                             "x-trust-lookup");
			if (uri != NULL)
				g_ptr_array_add (uris, uri);
		}
		g_ptr_array_add (uris, NULL);

		trust_lookup_uris = (gchar**)g_ptr_array_free (uris, FALSE);

		_gcr_debug ("trust store uri is: %s", trust_store_uri);
		debug = g_strjoinv (" ", trust_lookup_uris);
		_gcr_debug ("trust lookup uris are: %s", debug);
		g_free (debug);

		initialized_uris = TRUE;
	}

	G_UNLOCK (uris);
}
