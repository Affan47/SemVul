gyrus_session_treeview_on_key_press_event (GtkWidget *widget,
					   GdkEventKey *event,
					   gpointer user_data)
{
	GtkTreeSelection *selection;
	GtkTreeView *treeview = GTK_TREE_VIEW (widget);

	selection = gtk_tree_view_get_selection (treeview);

	if (gtk_tree_selection_count_selected_rows (selection) == 0)
		return FALSE;

	switch (event->keyval) {
	case GDK_Delete:
		gtk_button_clicked (GTK_BUTTON (button_delete));
		return TRUE;
	}

	return FALSE;
}
