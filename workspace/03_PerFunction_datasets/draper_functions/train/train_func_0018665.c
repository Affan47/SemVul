draw() {
	char old_lstyle[15];
	int old_join;
	double x, y;
	g_get_xy(&x, &y);
	g_get_line_style(old_lstyle);
	if (!(old_lstyle[0] == '1' && old_lstyle[1] == 0)) {
		g_set_line_style("1");
	}
	g_get_line_join(&old_join);
	if (old_join != 1) {
		g_set_line_join(1);
	}
	g_set_path(true);
	g_newpath();
	m_Side1.draw();
	m_Side2.draw();
	if (getStyle() != GLE_ARRSTY_SIMPLE) {
		g_closepath();
		GLERC<GLEColor> cur_color(g_get_color());
		GLERC<GLEColor> cur_full(g_get_fill());
		if (getStyle() == GLE_ARRSTY_EMPTY) g_set_fill(GLE_COLOR_WHITE);
		else g_set_fill(cur_color);
		g_fill();
		g_set_fill(cur_full);
	}
	if (!isSharp()) {
		g_stroke();
	}
	g_set_path(false);
	g_move(x, y);
	if (old_join != 1) {
		g_set_line_join(old_join);
	}
	if (!(old_lstyle[0] == '1' && old_lstyle[1] == 0)) {
		g_set_line_style(old_lstyle);
	}
}
