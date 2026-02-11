attach_directory_contents_value_field (NautilusPropertiesWindow *window,
				       GtkGrid *grid,
				       GtkWidget *sibling)
{
	GtkLabel *value_field;

	value_field = attach_value_label (grid, sibling, "");

	g_assert (window->details->directory_contents_value_field == NULL);
	window->details->directory_contents_value_field = value_field;

	gtk_label_set_line_wrap (value_field, TRUE);

	return value_field;
}
