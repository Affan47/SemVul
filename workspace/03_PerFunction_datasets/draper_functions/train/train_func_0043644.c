canvas_container_activate_previewer_callback (NautilusCanvasContainer *container,
					    GList *file_list,
					    GArray *locations,
					    NautilusCanvasView *canvas_view)
{
	g_assert (NAUTILUS_IS_CANVAS_VIEW (canvas_view));
	g_assert (container == get_canvas_container (canvas_view));

	nautilus_view_preview_files (NAUTILUS_VIEW (canvas_view),
				     file_list, locations);
}
