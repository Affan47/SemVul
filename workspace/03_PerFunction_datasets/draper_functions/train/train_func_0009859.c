load_modules (MonoImage *image)
{
	MonoTableInfo *t;

	if (image->modules)
		return;

	t = &image->tables [MONO_TABLE_MODULEREF];
	image->modules = g_new0 (MonoImage *, t->rows);
	image->modules_loaded = g_new0 (gboolean, t->rows);
	image->module_count = t->rows;
}
