eel_canvas_unmap (GtkWidget *widget)
{
	EelCanvas *canvas;

	g_return_if_fail (EEL_IS_CANVAS (widget));

	canvas = EEL_CANVAS (widget);

	shutdown_transients (canvas);


	if (EEL_CANVAS_ITEM_GET_CLASS (canvas->root)->unmap)
		(* EEL_CANVAS_ITEM_GET_CLASS (canvas->root)->unmap) (canvas->root);


	if (GTK_WIDGET_CLASS (canvas_parent_class)->unmap)
		(* GTK_WIDGET_CLASS (canvas_parent_class)->unmap) (widget);
}
