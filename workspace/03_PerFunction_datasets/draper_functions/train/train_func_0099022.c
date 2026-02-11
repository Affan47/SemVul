addrcompl_add_entry( CompletionWindow *cw, gchar *address ) {
	GtkListStore *store;
	GtkTreeIter iter;
	GtkTreeSelection *selection;
	gboolean is_group = FALSE;
	GList *grp_emails = NULL;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(cw->list_view)));
	GdkPixbuf *pixbuf;

	if (!group_pixbuf) {
		stock_pixbuf_gdk(cw->list_view, STOCK_PIXMAP_ADDR_TWO, &group_pixbuf);
		g_object_ref(G_OBJECT(group_pixbuf));
	}
	if (!email_pixbuf) {
		stock_pixbuf_gdk(cw->list_view, STOCK_PIXMAP_ADDR_ONE, &email_pixbuf);
		g_object_ref(G_OBJECT(email_pixbuf));
	}

	if (strstr(address, " <!--___group___-->")) {
		is_group = TRUE;
		if (_groupAddresses_)
			grp_emails = g_hash_table_lookup(_groupAddresses_, GINT_TO_POINTER(g_str_hash(address)));
		*(strstr(address, " <!--___group___-->")) = '\0';
		pixbuf = group_pixbuf;
	} else if (strchr(address, '@') && strchr(address, '<') &&
		   strchr(address, '>')) {
		pixbuf = email_pixbuf;
	} else
		pixbuf = NULL;

	if (is_group && !_allowCommas_)
		return;
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter,
				ADDR_COMPL_ICON, pixbuf,
				ADDR_COMPL_ADDRESS, address,
				ADDR_COMPL_ISGROUP, is_group,
				ADDR_COMPL_GROUPLIST, grp_emails,
				-1);
	cw->listCount++;


	addrcompl_resize_window( cw );
	gtk_grab_add( cw->window );

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(cw->list_view));
	gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);

	if( cw->listCount == 1 ) {

		gtk_tree_selection_select_iter(selection, &iter);
	}
#ifndef GENERIC_UMPC
	else if( cw->listCount == 2 ) {
		gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);

		gtk_tree_selection_select_iter(selection, &iter);
	}
#endif
}
