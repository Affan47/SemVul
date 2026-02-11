eel_canvas_item_grab_focus (EelCanvasItem *item)
{
	EelCanvasItem *focused_item;
	GdkEvent ev;

	g_return_if_fail (EEL_IS_CANVAS_ITEM (item));
	g_return_if_fail (gtk_widget_get_can_focus (GTK_WIDGET (item->canvas)));

	focused_item = item->canvas->focused_item;

	if (focused_item) {
		ev.focus_change.type = GDK_FOCUS_CHANGE;
		ev.focus_change.window = gtk_layout_get_bin_window (GTK_LAYOUT (item->canvas));
		ev.focus_change.send_event = FALSE;
		ev.focus_change.in = FALSE;

		emit_event (item->canvas, &ev);
	}

	item->canvas->focused_item = item;
	gtk_widget_grab_focus (GTK_WIDGET (item->canvas));

	if (focused_item) {
		ev.focus_change.type = GDK_FOCUS_CHANGE;
		ev.focus_change.window = gtk_layout_get_bin_window (GTK_LAYOUT (item->canvas));
		ev.focus_change.send_event = FALSE;
		ev.focus_change.in = TRUE;

		emit_event (item->canvas, &ev);
	}
}
