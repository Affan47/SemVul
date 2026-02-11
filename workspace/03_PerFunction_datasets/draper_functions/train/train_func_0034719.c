Append(char *s, int type) {
	ListImage *list_image = NULL;
	if ((type >= 0) && pixhash) {
		list_image = static_cast<ListImage *>(g_hash_table_lookup((GHashTable *) pixhash
		             , (gconstpointer) GINT_TO_POINTER(type)));
	}
	GtkTreeIter iter;
	GtkListStore *store =
		GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	gtk_list_store_append(GTK_LIST_STORE(store), &iter);
	if (list_image) {
		if (NULL == list_image->pixbuf)
			init_pixmap(list_image);
		if (list_image->pixbuf) {
			gtk_list_store_set(GTK_LIST_STORE(store), &iter,
								PIXBUF_COLUMN, list_image->pixbuf,
								TEXT_COLUMN, s, -1);

			gint pixbuf_width = gdk_pixbuf_get_width(list_image->pixbuf);
			gint renderer_height, renderer_width;
			gtk_cell_renderer_get_fixed_size(pixbuf_renderer,
								&renderer_width, &renderer_height);
			if (pixbuf_width > renderer_width)
				gtk_cell_renderer_set_fixed_size(pixbuf_renderer,
								pixbuf_width, -1);
		} else {
			gtk_list_store_set(GTK_LIST_STORE(store), &iter,
								TEXT_COLUMN, s, -1);
		}
	} else {
			gtk_list_store_set(GTK_LIST_STORE(store), &iter,
								TEXT_COLUMN, s, -1);
	}
	size_t len = strlen(s);
	if (maxItemCharacters < len)
		maxItemCharacters = len;
}
