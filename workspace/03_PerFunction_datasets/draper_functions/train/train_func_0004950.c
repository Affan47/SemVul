nautilus_canvas_dnd_begin_drag (NautilusCanvasContainer *container,
			      GdkDragAction actions,
			      int button,
			      GdkEventMotion *event,
			      int                    start_x,
			      int                    start_y)
{
	NautilusCanvasDndInfo *dnd_info;

	g_return_if_fail (NAUTILUS_IS_CANVAS_CONTAINER (container));
	g_return_if_fail (event != NULL);

	dnd_info = container->details->dnd_info;
	g_return_if_fail (dnd_info != NULL);


	dnd_info->drag_info.start_x = start_x -
		gtk_adjustment_get_value (gtk_scrollable_get_hadjustment (GTK_SCROLLABLE (container)));
	dnd_info->drag_info.start_y = start_y -
		gtk_adjustment_get_value (gtk_scrollable_get_vadjustment (GTK_SCROLLABLE (container)));


	gtk_drag_begin_with_coordinates (GTK_WIDGET (container),
					 dnd_info->drag_info.target_list,
					 actions,
					 button,
					 (GdkEvent *) event,
					 dnd_info->drag_info.start_x,
					 dnd_info->drag_info.start_y);
}
