create_formats_list (GtkWidget       *listview,
		     const gchar     *sel_format,
		     GeditTimePlugin *plugin)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *cell;

	gedit_debug (DEBUG_PLUGINS);

	g_return_if_fail (listview != NULL);
	g_return_if_fail (sel_format != NULL);


	cell = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes (
			_("Available formats"),
			cell,
			"text", COLUMN_FORMATS,
			NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);


	create_model (listview, sel_format, plugin);

	g_signal_connect (listview,
			  "realize",
			  G_CALLBACK (scroll_to_selected),
			  NULL);

	gtk_widget_show (listview);
}
