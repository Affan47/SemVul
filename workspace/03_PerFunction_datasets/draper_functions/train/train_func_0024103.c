cb_width_changed (GtkAdjustment *adj, GogErrorBarEditor *editor)
{
	editor->width = gtk_adjustment_get_value (adj);
	if (editor->bar) {
		editor->bar->width = gtk_adjustment_get_value (adj);
		gog_object_request_update (GOG_OBJECT (editor->series));
	}
}
