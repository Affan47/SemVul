nautilus_canvas_view_set_directory_sort_by (NautilusCanvasView *canvas_view,
					  NautilusFile *file,
					  const char *sort_by)
{
	const SortCriterion *default_sort_criterion;

	if (!nautilus_canvas_view_supports_auto_layout (canvas_view)) {
		return;
	}

	default_sort_criterion = get_sort_criterion_by_sort_type (get_default_sort_order (file, NULL));
	g_return_if_fail (default_sort_criterion != NULL);

	nautilus_file_set_metadata
		(file, NAUTILUS_METADATA_KEY_ICON_VIEW_SORT_BY,
		 default_sort_criterion->metadata_text,
		 sort_by);
}
