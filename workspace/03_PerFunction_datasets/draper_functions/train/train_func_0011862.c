gdb_merge_preferences (AnjutaPreferences* prefs, GList **list)
{
	GtkBuilder *bxml;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeSelection *selection;
	PreferenceDialog *dlg;
	GList *item;

	g_return_if_fail (list != NULL);


	bxml =  anjuta_util_builder_new (BUILDER_FILE, NULL);
	if (!bxml) return;

	dlg = g_new0 (PreferenceDialog, 1);


	anjuta_util_builder_get_objects (bxml,
		GDB_PRINTER_TREEVIEW, &dlg->treeview,
		GDB_PRINTER_REMOVE_BUTTON, &dlg->remove_button,
		NULL);


	dlg->model = gtk_list_store_new (GDB_PP_N_COLUMNS,
		G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model (dlg->treeview, GTK_TREE_MODEL (dlg->model));
	g_object_unref (dlg->model);

	renderer = gtk_cell_renderer_toggle_new ();
	g_signal_connect (G_OBJECT (renderer), "toggled", G_CALLBACK (gdb_on_printer_activate), dlg);
	column = gtk_tree_view_column_new_with_attributes (_("Activate"), renderer,
		"active", GDB_PP_ACTIVE_COLUMN, NULL);
	gtk_tree_view_append_column (dlg->treeview, column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes (_("File"), renderer,
		"text", GDB_PP_FILENAME_COLUMN, NULL);
	gtk_tree_view_append_column (dlg->treeview, column);

	renderer = gtk_cell_renderer_text_new ();
	g_object_set(renderer, "editable", TRUE, NULL);
	g_signal_connect(renderer, "edited", G_CALLBACK (gdb_on_printer_function_changed), dlg);


	column = gtk_tree_view_column_new_with_attributes (_("Register Function"), renderer,
		"text", GDB_PP_REGISTER_COLUMN, NULL);
	gtk_tree_view_append_column (dlg->treeview, column);


	gtk_builder_connect_signals (bxml, dlg);
	selection = gtk_tree_view_get_selection (dlg->treeview);
	g_signal_connect (G_OBJECT (selection), "changed", G_CALLBACK (gdb_on_printer_selection_changed), dlg);


	dlg->list = list;
	for (item = g_list_first (*list); item != NULL; item = g_list_next (item))
	{
		GdbPrettyPrinter *printer = (GdbPrettyPrinter *)item->data;
		GtkTreeIter iter;

		gtk_list_store_append (dlg->model, &iter);
		gtk_list_store_set (dlg->model, &iter, GDB_PP_ACTIVE_COLUMN, printer->enable ? TRUE : FALSE,
											GDB_PP_FILENAME_COLUMN, printer->path,
											GDB_PP_REGISTER_COLUMN, printer->function,
											-1);
	}

	anjuta_preferences_add_from_builder (prefs, bxml, NULL, GDB_PREFS_ROOT, _("Gdb Debugger"),  ICON_FILE);

	g_object_unref (bxml);
}
