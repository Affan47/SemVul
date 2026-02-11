create_snippets_tree_view (SnippetsDB *snippets_db,
                           GtkTreeStore *snippets_tree_store)
{
	GtkWidget *snippets_tree_view = NULL;
	GtkTreeViewColumn *column = NULL;
	GtkCellRenderer   *text_renderer = NULL, *toggle_renderer = NULL;


	g_return_val_if_fail (ANJUTA_IS_SNIPPETS_DB (snippets_db), NULL);


	snippets_tree_view = gtk_tree_view_new();
	gtk_tree_view_set_model (GTK_TREE_VIEW (snippets_tree_view),
	                         GTK_TREE_MODEL (snippets_tree_store));


	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title  (column, "Name");
	gtk_tree_view_append_column     (GTK_TREE_VIEW (snippets_tree_view),
	                                 column);
	toggle_renderer = gtk_cell_renderer_toggle_new();

	g_signal_connect (toggle_renderer, "toggled", G_CALLBACK (handle_toggle), snippets_tree_store);

	gtk_tree_view_column_pack_start (column,
	                                 toggle_renderer,
	                                 TRUE);

	gtk_tree_view_column_add_attribute (column,
	                                    toggle_renderer,
	                                    "active", SNIPPETS_STORE_COL_ACTIVE);

	text_renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start (column,
	                                 text_renderer,
	                                 TRUE);

	gtk_tree_view_column_set_cell_data_func (column, text_renderer,
	                                         snippets_view_name_data_func,
	                                         snippets_tree_view, NULL);


	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title  (column, "Trigger");
	gtk_tree_view_append_column     (GTK_TREE_VIEW (snippets_tree_view),
	                                 column);
	text_renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start (column,
	                                 text_renderer,
	                                 TRUE);

	gtk_tree_view_column_set_cell_data_func (column, text_renderer,
	                                         snippets_view_trigger_data_func,
	                                         snippets_tree_view, NULL);


	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_title  (column, "Languages");
	gtk_tree_view_append_column     (GTK_TREE_VIEW (snippets_tree_view),
	                                 column);
	text_renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start (column,
	                                 text_renderer,
	                                 TRUE);

	gtk_tree_view_column_set_cell_data_func (column, text_renderer,
	                                         snippets_view_languages_data_func,
	                                         snippets_tree_view, NULL);
	return snippets_tree_view;
}
