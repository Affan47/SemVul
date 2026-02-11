ect_max_width_by_row (ECellView *ecell_view,
                      gint model_col,
                      gint view_col,
                      gint row)
{

	ECellTextView *text_view = (ECellTextView *) ecell_view;
	gint width;
	PangoLayout *layout;

	if (row >= e_table_model_row_count (ecell_view->e_table_model))
		return 0;

	layout = generate_layout (text_view, model_col, view_col, row, 0);
	pango_layout_get_pixel_size (layout, &width, NULL);
	g_object_unref (layout);

	return width + 8;
}
