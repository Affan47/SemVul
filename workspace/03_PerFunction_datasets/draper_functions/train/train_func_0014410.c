cpp_packages_activate_package (IAnjutaSymbolManager* sm, const gchar* pkg,
                               GList** packages_to_add)
{
	gchar* name = g_strdup (pkg);
	gchar* version;
	gchar* c;


	for (c = name; *c != '\0'; c++)
	{
		if (g_ascii_isspace (*c))
		{
			*c = '\0';
			break;
		}
	}

	version = anjuta_pkg_config_get_version (name);
	if (!version)
	{
		g_free (name);
		return *packages_to_add;
	}


	if (g_list_find_custom (*packages_to_add,
	                        name, (GCompareFunc) pkg_data_compare))
		return *packages_to_add;
	if (!ianjuta_symbol_manager_activate_package (sm, name, version, NULL))
	{
		GList* deps = anjuta_pkg_config_list_dependencies (name, NULL);
		GList* dep;
		PackageData* data = g_new0 (PackageData, 1);
		for (dep = deps; dep != NULL; dep = g_list_next (dep))
		{
			cpp_packages_activate_package (sm, dep->data, packages_to_add);
		}
		anjuta_util_glist_strings_free (deps);
		data->pkg = g_strdup (name);
		data->version = g_strdup (version);
		*packages_to_add = g_list_prepend (*packages_to_add,
		                                   data);
	}
	g_free (name);
	return *packages_to_add;
}
