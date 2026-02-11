nautilus_canvas_view_container_compare_icons (NautilusCanvasContainer *container,
					    NautilusCanvasIconData      *icon_a,
					    NautilusCanvasIconData      *icon_b)
{
	NautilusCanvasView *canvas_view;

	canvas_view = get_canvas_view (container);
	g_return_val_if_fail (canvas_view != NULL, 0);

	if (NAUTILUS_CANVAS_VIEW_CONTAINER (container)->sort_for_desktop) {
		return fm_desktop_canvas_container_icons_compare
			(container, icon_a, icon_b);
	}


	return nautilus_canvas_view_compare_files (canvas_view,
					   (NautilusFile *)icon_a,
					   (NautilusFile *)icon_b);
}
