e2_option_tree_setup_defaults (E2_OptionSet *set, gchar *first, ...)
{
	if (first == NULL) return;

	va_list args;
	va_start (args, first);
	gchar *cur = first;
	GPtrArray *lines = g_ptr_array_sized_new (32);
	while (cur)
	{


		g_ptr_array_add (lines, (gpointer) cur);
		cur = va_arg (args, gchar *);
	}
	va_end (args);

	g_ptr_array_add (lines, NULL);
	set->ex.tree.def = lines->pdata;
	g_ptr_array_free (lines, FALSE);
}
