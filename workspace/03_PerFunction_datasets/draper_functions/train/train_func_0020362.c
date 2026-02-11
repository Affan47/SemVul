control_config_scroll_screen_up()
{
	if (Scroll_offset) {
		Scroll_offset--;
		Assert(Selected_line > Scroll_offset);
		while (!cc_line_query_visible(Selected_line)) {
			Selected_line--;
		}

		Selected_item = -1;
		gamesnd_play_iface(SND_SCROLL);

	} else {
		gamesnd_play_iface(SND_GENERAL_FAIL);
	}
}
