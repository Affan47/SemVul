set_print_flag (SheetObject *so, gboolean print)
{
	gboolean *p_print = g_new (gboolean, 1);

	*p_print = print;
	return go_undo_binary_new
		(g_object_ref (so), p_print,
		 (GOUndoBinaryFunc)sheet_object_set_print_flag,
		 g_object_unref, g_free);
}
