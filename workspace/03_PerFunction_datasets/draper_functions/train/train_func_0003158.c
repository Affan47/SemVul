nautilus_canvas_view_container_unfreeze_updates (NautilusCanvasContainer *container)
{
	NautilusCanvasView *canvas_view;
	canvas_view = get_canvas_view (container);
	g_return_if_fail (canvas_view != NULL);
	nautilus_view_unfreeze_updates (NAUTILUS_VIEW (canvas_view));
}
