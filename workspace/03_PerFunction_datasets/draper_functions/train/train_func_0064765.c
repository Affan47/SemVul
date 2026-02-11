button_press_event(GtkWidget *widget, GdkEventButton *event,
    gpointer data)
{
	struct coord pos = canvas_to_coord(event->x, event->y);
	int res;

	DPRINTF("--- button press ---");
	gtk_widget_grab_focus(widget);
	switch (event->button) {
	case 1:
		if (dragging) {
			fprintf(stderr, "HUH ?!?\n");
			tool_cancel_drag();
			dragging = 0;
		}
		res = tool_consider_drag(pos);

		if (res < 0) {
			change_world();
			inst_deselect();
			break;
		}
		if (res) {
			selected_before_drag = selected_inst;
			inst_deselect();
			redraw();
			dragging = 1;
			drag_escaped = 0;
			drag_start = pos;
			break;
		}
		click_to_select(pos);
		break;
	case 2:
		tool_dehover();
		draw_ctx.center = pos;
		redraw();
		tool_hover(canvas_to_coord(event->x, event->y));
		break;
	}
	return TRUE;
}
