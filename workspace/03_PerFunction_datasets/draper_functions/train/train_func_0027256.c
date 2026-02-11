goal_screen_scroll_down()
{
	int max_lines;

	max_lines = Goal_screen_text_h / gr_get_font_height();
	if (Scroll_offset + max_lines < Goal_text.m_num_lines) {
		Scroll_offset++;
		gamesnd_play_iface(SND_SCROLL);
	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}
