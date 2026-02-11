get_shadow_assembly_location_base (MonoDomain *domain, MonoError *error)
{
	MonoAppDomainSetup *setup;
	char *cache_path, *appname;
	char *userdir;
	char *location;

	mono_error_init (error);

	setup = domain->setup;
	if (setup->cache_path != NULL && setup->application_name != NULL) {
		cache_path = mono_string_to_utf8_checked (setup->cache_path, error);
		if (!mono_error_ok (error))
			return NULL;
#ifndef TARGET_WIN32
		{
			gint i;
			for (i = strlen (cache_path) - 1; i >= 0; i--)
				if (cache_path [i] == '\\')
					cache_path [i] = '/';
		}
#endif

		appname = mono_string_to_utf8_checked (setup->application_name, error);
		if (!mono_error_ok (error)) {
			g_free (cache_path);
			return NULL;
		}

		location = g_build_filename (cache_path, appname, "assembly", "shadow", NULL);
		g_free (appname);
		g_free (cache_path);
	} else {
		userdir = g_strdup_printf ("%s-mono-cachepath", g_get_user_name ());
		location = g_build_filename (g_get_tmp_dir (), userdir, "assembly", "shadow", NULL);
		g_free (userdir);
	}
	return location;
}
