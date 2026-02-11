nautilus_canvas_container_start_monitor_top_left (NautilusCanvasContainer *container,
						  NautilusCanvasIconData *data,
						  gconstpointer client,
						  gboolean large_text)
{
	NautilusCanvasContainerClass *klass;

	klass = NAUTILUS_CANVAS_CONTAINER_GET_CLASS (container);
	g_assert (klass->start_monitor_top_left != NULL);

	klass->start_monitor_top_left (container, data, client, large_text);
}
