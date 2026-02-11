perl_settings_add(const char *key)
{
	PERL_SCRIPT_REC *script;
        GSList *list;

	script = perl_script_find_package(perl_get_package());
	g_return_if_fail(script != NULL);

	list = g_hash_table_lookup(perl_settings, script);
        list = g_slist_append(list, g_strdup(key));
	g_hash_table_insert(perl_settings, script, list);
}
