cutscenes_screen_scroll_line_up()
{
	if (Selected_line) {
		Selected_line--;
		gamesnd_play_iface(SND_SCROLL);

	} else
		gamesnd_play_iface(SND_GENERAL_FAIL);

	if (Selected_line < Scroll_offset)
		Scroll_offset = Selected_line;
}
