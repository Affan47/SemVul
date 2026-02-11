view_history_revision_list_key_press_cb (GiggleRevListView *list,
					 GdkEventKey        *event,
					 GiggleViewHistory  *view)
{
	GiggleViewHistoryPriv *priv;
	GtkTreePath           *path, *start, *end;
	GtkTreeSelection      *selection;
	GtkAdjustment         *adj;
	gdouble                value;
	gdouble                adj_value;
	gdouble                page_size;

	priv = view->priv;

	if (event->keyval != GDK_KEY_space &&
	    event->keyval != GDK_KEY_BackSpace)
		return FALSE;

	giggle_view_shell_set_view_name (GIGGLE_VIEW_SHELL (priv->revision_shell), "DiffView");
	adj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (priv->revision_list_sw));

	adj_value = gtk_adjustment_get_value (adj);
	page_size = gtk_adjustment_get_page_size (adj);

	value = event->keyval == GDK_KEY_space ?
		adj_value + (page_size * 0.8) :
		adj_value - (page_size * 0.8);

	value = CLAMP (value, gtk_adjustment_get_lower (adj), gtk_adjustment_get_upper (adj) - page_size);
	gtk_adjustment_set_value (adj, value);

	if (gtk_tree_view_get_visible_range (GTK_TREE_VIEW (priv->revision_list), &start, &end)) {
		selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->revision_list));
		path = event->keyval == GDK_KEY_space ? end : start;

		gtk_tree_selection_unselect_all (selection);
		gtk_tree_selection_select_path (selection, path);

		gtk_tree_view_scroll_to_cell (GTK_TREE_VIEW (priv->revision_list),
					      path, NULL, FALSE, 0, 0);

		gtk_tree_path_free (start);
		gtk_tree_path_free (end);
	}

	return TRUE;
}
