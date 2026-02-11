mimeview_button_pressed(GtkWidget *widget, GdkEventButton *event,
				    MimeView *mimeview)
{
	GtkTreeSelection *selection;
	GtkTreeIter iter;

	if (!event) return FALSE;

	if (event->button == 2 || event->button == 3) {
		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
		if (!gtk_tree_selection_get_selected(selection, NULL, &iter))
			return FALSE;

		gtk_tree_selection_select_iter(selection, &iter);
	}
	part_button_pressed(mimeview, event, mimeview_get_selected_part(mimeview));

	return FALSE;
}
