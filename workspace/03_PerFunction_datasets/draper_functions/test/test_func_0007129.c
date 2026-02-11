theme_module_create(THEME_REC *theme, const char *module)
{
	MODULE_THEME_REC *rec;
	FORMAT_REC *formats;

	rec = g_hash_table_lookup(theme->modules, module);
	if (rec != NULL) return rec;

	formats = g_hash_table_lookup(default_formats, module);
        g_return_val_if_fail(formats != NULL, NULL);

	rec = g_new0(MODULE_THEME_REC, 1);
	rec->name = g_strdup(module);

	for (rec->count = 0; formats[rec->count].def != NULL; rec->count++) ;
	rec->formats = g_new0(char *, rec->count);
	rec->expanded_formats = g_new0(char *, rec->count);

	g_hash_table_insert(theme->modules, rec->name, rec);
	return rec;
}
