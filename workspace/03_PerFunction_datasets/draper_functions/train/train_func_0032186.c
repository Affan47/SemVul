ganv_canvas_base_size_allocate(GtkWidget* widget, GtkAllocation* allocation)
{
	GanvCanvasBase* canvas;

	g_return_if_fail(GANV_IS_CANVAS_BASE(widget));
	g_return_if_fail(allocation != NULL);

	if (GTK_WIDGET_CLASS(canvas_parent_class)->size_allocate) {
		(*GTK_WIDGET_CLASS(canvas_parent_class)->size_allocate)(widget, allocation);
	}

	canvas = GANV_CANVAS_BASE(widget);


	canvas->layout.hadjustment->page_size      = allocation->width;
	canvas->layout.hadjustment->page_increment = allocation->width / 2;

	canvas->layout.vadjustment->page_size      = allocation->height;
	canvas->layout.vadjustment->page_increment = allocation->height / 2;

	scroll_to(canvas,
	          canvas->layout.hadjustment->value,
	          canvas->layout.vadjustment->value);

	g_signal_emit_by_name(canvas->layout.hadjustment, "changed");
	g_signal_emit_by_name(canvas->layout.vadjustment, "changed");
}
