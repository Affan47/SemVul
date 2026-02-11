eel_canvas_accessible_all_parents_visible (GtkWidget *widget)
{
	GtkWidget *iter_parent = NULL;
	gboolean result = TRUE;

	for (iter_parent = gtk_widget_get_parent (widget); iter_parent != NULL;
	     iter_parent = gtk_widget_get_parent (iter_parent)) {
		if (!gtk_widget_get_visible (iter_parent)) {
			result = FALSE;
			break;
		}
	}

	return result;
}
