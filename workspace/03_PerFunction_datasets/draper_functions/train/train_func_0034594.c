display(int n, int y)
{
	int y1, w, h;
	char buf[MAX_GOAL_TEXT];

	if ((n < 0) || (n >= m_num_lines) || (m_line_sizes[n] < 1))
		return;

	Assert(m_line_sizes[n] < MAX_GOAL_TEXT);
	y += Goal_screen_text_y;
	if (*m_lines[n] == '*') {
		gr_set_color_fast(&Color_text_heading);
		strncpy(buf, m_lines[n] + 1, m_line_sizes[n] - 1);
		buf[m_line_sizes[n] - 1] = 0;

		gr_get_string_size(&w, &h, buf);
		y1 = y + h / 2 - 1;


		gr_line(Goal_screen_icon_x, y1, Goal_screen_text_x - 2, y1);
		gr_line(Goal_screen_text_x + w + 1, y1, Goal_screen_icon_x + Goal_screen_text_w, y1);

	} else {
		gr_set_color_fast(&Color_text_normal);
		strncpy(buf, m_lines[n], m_line_sizes[n]);
		buf[m_line_sizes[n]] = 0;
	}

	gr_printf(Goal_screen_text_x, y, buf);
}
