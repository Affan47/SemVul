on_name_field_changed (GtkEditable *editable,
		       gpointer     user_data)
{
	NautilusBookmarksWindow *self = user_data;
	GtkTreeIter   iter;

	if (!get_selection_exists(self)) {
		return;
	}


	gtk_tree_selection_get_selected (self->priv->selection, NULL, &iter);
	gtk_list_store_set (self->priv->model,
			    &iter, BOOKMARK_LIST_COLUMN_NAME,
			    gtk_entry_get_text (GTK_ENTRY (self->priv->name_field)),
			    -1);

	self->priv->text_changed = TRUE;
}
