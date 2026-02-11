ganv_canvas_base_motion(GtkWidget* widget, GdkEventMotion* event)
{
	GanvCanvasBase* canvas;

	g_return_val_if_fail(GANV_IS_CANVAS_BASE(widget), FALSE);
	g_return_val_if_fail(event != NULL, FALSE);

	canvas = GANV_CANVAS_BASE(widget);

	if (event->window != canvas->layout.bin_window) {
		return FALSE;
	}

	canvas->state = event->state;
	pick_current_item(canvas, (GdkEvent*)event);
	return emit_event(canvas, (GdkEvent*)event);
}
