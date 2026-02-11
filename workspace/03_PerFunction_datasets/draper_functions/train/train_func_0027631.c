ganv_item_grab_focus(GanvItem* item)
{
	GanvItem* focused_item;
	GdkEvent  ev;

	g_return_if_fail(GANV_IS_ITEM(item));
	g_return_if_fail(GTK_WIDGET_CAN_FOCUS(GTK_WIDGET(item->canvas)));

	focused_item = item->canvas->focused_item;

	if (focused_item) {
		ev.focus_change.type       = GDK_FOCUS_CHANGE;
		ev.focus_change.window     = GTK_LAYOUT(item->canvas)->bin_window;
		ev.focus_change.send_event = FALSE;
		ev.focus_change.in         = FALSE;

		emit_event(item->canvas, &ev);
	}

	item->canvas->focused_item = item;
	gtk_widget_grab_focus(GTK_WIDGET(item->canvas));

	if (focused_item) {
		ev.focus_change.type       = GDK_FOCUS_CHANGE;
		ev.focus_change.window     = GTK_LAYOUT(item->canvas)->bin_window;
		ev.focus_change.send_event = FALSE;
		ev.focus_change.in         = TRUE;

		emit_event(item->canvas, &ev);
	}
}
