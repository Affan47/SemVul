bookmarks_set_empty (NautilusBookmarksWindow *self,
		     gboolean empty)
{
	GtkTreeIter iter;

	if (empty) {
		setup_empty_list (self);
		gtk_widget_set_sensitive (GTK_WIDGET (self->priv->tree_view), FALSE);
	} else {
		gtk_tree_view_set_model (self->priv->tree_view, GTK_TREE_MODEL (self->priv->model));
		gtk_widget_set_sensitive (GTK_WIDGET (self->priv->tree_view), TRUE);

		if (nautilus_bookmark_list_length (self->priv->bookmarks) > 0 &&
		    !get_selection_exists (self)) {
			gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (self->priv->model),
						       &iter, NULL, 0);
			gtk_tree_selection_select_iter (self->priv->selection, &iter);
		}
	}

	on_selection_changed (self->priv->selection, self);
}
