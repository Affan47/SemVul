search_result_release_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	MatchFileData *mfd = NULL;

	if (bevent->button != MOUSE_BUTTON_LEFT && bevent->button != MOUSE_BUTTON_MIDDLE) return TRUE;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));

	if ((bevent->x != 0 || bevent->y != 0) &&
	    gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), bevent->x, bevent->y,
					  &tpath, NULL, NULL, NULL))
		{
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &mfd, -1);
		gtk_tree_path_free(tpath);
		}

	if (bevent->button == MOUSE_BUTTON_MIDDLE)
		{
		if (mfd && sd->click_fd == mfd->fd)
			{
			GtkTreeSelection *selection;

			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
			if (search_result_row_selected(sd, mfd->fd))
				{
				gtk_tree_selection_unselect_iter(selection, &iter);
				}
			else
				{
				gtk_tree_selection_select_iter(selection, &iter);
				}
			}
		return TRUE;
		}

	if (mfd && sd->click_fd == mfd->fd &&
	    !(bevent->state & GDK_SHIFT_MASK ) &&
	    !(bevent->state & GDK_CONTROL_MASK ) &&
	    search_result_row_selected(sd, mfd->fd))
		{
		GtkTreeSelection *selection;

		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
		gtk_tree_selection_unselect_all(selection);
		gtk_tree_selection_select_iter(selection, &iter);

		tpath = gtk_tree_model_get_path(store, &iter);
		gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), tpath, NULL, FALSE);
		gtk_tree_path_free(tpath);

		return TRUE;
		}

	return FALSE;
}
