brasero_audio_disc_add_pause (BraseroAudioDisc *disc)
{
	GtkTreeSelection *selection;
	GtkTreePath *treepath;
	GtkTreeModel *model;
	GList *references = NULL;
	GList *selected;
	GList *iter;

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (disc->priv->tree));
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (disc->priv->tree));
	selected = gtk_tree_selection_get_selected_rows (selection, &model);


	for (iter = selected; iter; iter = iter->next) {
		GtkTreeRowReference *ref;

		treepath = iter->data;
		ref = gtk_tree_row_reference_new (model, treepath);
		references = g_list_append (references, ref);
	}

	g_list_foreach (selected, (GFunc) gtk_tree_path_free, NULL);
	g_list_free (selected);

	for (iter = references; iter; iter = iter->next) {
		GtkTreeRowReference *ref;

		ref = iter->data;
		treepath = gtk_tree_row_reference_get_path (ref);
		gtk_tree_row_reference_free (ref);

		brasero_audio_disc_add_gap (disc, treepath, 2 * GST_SECOND);
		gtk_tree_path_free (treepath);
	}

	g_list_free (references);
}
