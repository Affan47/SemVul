message_view_on_column_click(GtkTreeViewColumn * column, gpointer user_data)
{
	gint column_id = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(column), "column id"));
	message_view_t *view = (message_view_t *) user_data;
	int dir = 0;
	seaudit_sort_t *sort;
	GtkTreeViewColumn *prev_column;
	if (column_id == view->store->sort_field) {
		dir = view->store->sort_dir * -1;
	} else {
		dir = 1;
	}

	if ((sort = column_data[(preference_field_e) column_id].sort(dir)) == NULL) {
		toplevel_ERR(view->top, "%s", strerror(errno));
		return TRUE;
	}
	seaudit_model_clear_sorts(view->model);
	if (seaudit_model_append_sort(view->model, sort) < 0) {
		seaudit_sort_destroy(&sort);
		toplevel_ERR(view->top, "%s", strerror(errno));
	}
	prev_column = gtk_tree_view_get_column(view->view, view->store->sort_field);
	if (prev_column != NULL) {
		gtk_tree_view_column_set_sort_indicator(prev_column, FALSE);
	}
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	if (dir > 0) {
		gtk_tree_view_column_set_sort_order(column, GTK_SORT_ASCENDING);
	} else {
		gtk_tree_view_column_set_sort_order(column, GTK_SORT_DESCENDING);
	}

	view->store->sort_field = column_id;
	view->store->sort_dir = dir;
	message_view_update_rows(view);
	return TRUE;
}
