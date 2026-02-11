display_cursor()
{
	struct widget *w;
	w = get_active_widget(GetMousePos_x(), GetMousePos_y());

	if (w) {
		if (w->type != WIDGET_MAP)
			blit_mouse_cursor();
		else
			widget_lvledit_map_display_cursor();
	}
}
