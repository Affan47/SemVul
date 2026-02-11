nautilus_canvas_container_is_layout_rtl (NautilusCanvasContainer *container)
{
	g_return_val_if_fail (NAUTILUS_IS_CANVAS_CONTAINER (container), 0);

	return (gtk_widget_get_direction (GTK_WIDGET (container)) == GTK_TEXT_DIR_RTL);
}
