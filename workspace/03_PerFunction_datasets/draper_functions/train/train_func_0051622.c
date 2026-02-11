term_data_destroy(term_data *td)
{
	if (GTK_IS_WIDGET(td->drawing_area))
		gtk_widget_destroy(td->drawing_area);
	if (GTK_IS_WIDGET(td->win))
		gtk_widget_destroy(td->win);
	if (cairo_surface_get_reference_count(td->surface) > 0)
		cairo_surface_destroy(td->surface);
}
