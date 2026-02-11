gnm_simple_canvas_key_press (GtkWidget *widget, GdkEventKey *event)
{
	GnmSimpleCanvas *gcanvas = GNM_SIMPLE_CANVAS (widget);

	if (gcanvas->scg->grab_stack > 0)
		return TRUE;
	return parent->key_press_event (widget, event);
}
