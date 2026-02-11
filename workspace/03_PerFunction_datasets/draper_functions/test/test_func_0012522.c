cb_dialog_doc_metadata_keywords_remove_clicked (G_GNUC_UNUSED GtkWidget *w,
						DialogDocMetaData       *state)
{
	GtkTreeIter iter;
	GtkTreeSelection *sel = gtk_tree_view_get_selection (state->key_tree_view);

	if (gtk_tree_selection_get_selected (sel, NULL, &iter)) {
		gtk_list_store_remove (state->key_store, &iter);
		dialog_doc_metadata_update_keywords_changed (state);
	}
}
