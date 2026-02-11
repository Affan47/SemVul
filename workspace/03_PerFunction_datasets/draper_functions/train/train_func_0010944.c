inv_knob_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_return_val_if_fail(widget != NULL, FALSE);
	g_return_val_if_fail(INV_IS_KNOB(widget), FALSE);
	g_return_val_if_fail(event != NULL, FALSE);

	inv_knob_paint(widget,INV_KNOB_DRAW_ALL);

	return FALSE;
}
