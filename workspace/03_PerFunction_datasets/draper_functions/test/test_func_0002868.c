update_bookmark_from_text (NautilusBookmarksWindow *self)
{
	NautilusBookmark *bookmark, *bookmark_in_list;
	const char *name;
	GIcon *icon;
	guint selected_row;
	GtkTreeIter iter;
	GFile *location;

	if (!self->priv->text_changed ||
	    gtk_entry_get_text_length (GTK_ENTRY (self->priv->uri_field)) == 0) {
		return;
	}

	location = g_file_parse_name
		(gtk_entry_get_text (GTK_ENTRY (self->priv->uri_field)));

	bookmark = nautilus_bookmark_new (location,
					  gtk_entry_get_text (GTK_ENTRY (self->priv->name_field)));

	g_object_unref (location);

	selected_row = get_selected_row (self);


	g_signal_handler_block (self->priv->bookmarks, self->priv->bookmarks_changed_id);
	nautilus_bookmark_list_delete_item_at (self->priv->bookmarks, selected_row);
	nautilus_bookmark_list_insert_item (self->priv->bookmarks, bookmark, selected_row);
	g_signal_handler_unblock (self->priv->bookmarks, self->priv->bookmarks_changed_id);
	g_object_unref (bookmark);


	gtk_tree_selection_get_selected (self->priv->selection, NULL, &iter);
	g_signal_handler_block (self->priv->model, self->priv->row_changed_id);

	bookmark_in_list = nautilus_bookmark_list_item_at (self->priv->bookmarks, selected_row);
	name = nautilus_bookmark_get_name (bookmark_in_list);
	icon = nautilus_bookmark_get_symbolic_icon (bookmark_in_list);

	gtk_list_store_set (self->priv->model, &iter,
			    BOOKMARK_LIST_COLUMN_BOOKMARK, bookmark_in_list,
			    BOOKMARK_LIST_COLUMN_NAME, name,
			    BOOKMARK_LIST_COLUMN_ICON, icon,
			    -1);

	g_signal_handler_unblock (self->priv->model, self->priv->row_changed_id);
	g_object_unref (icon);
}
