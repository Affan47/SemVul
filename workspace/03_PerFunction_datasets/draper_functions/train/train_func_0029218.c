draw_cb (GtkDrawingArea *drawing_area,
		 cairo_t *cr,
		 gpointer  user_data)
{
	update_relative_sizes (EOG_PRINT_PREVIEW (user_data));

	eog_print_preview_draw (EOG_PRINT_PREVIEW (user_data), cr);

	if (cairo_status (cr) != CAIRO_STATUS_SUCCESS) {
		fprintf (stderr, "Cairo is unhappy: %s\n",
			 cairo_status_to_string (cairo_status (cr)));
	}

	return TRUE;
}
