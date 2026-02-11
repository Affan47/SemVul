GoToNextTab(void)
{
	for (;;) {
		UBYTE prev = video_ram[curs];
		if (prev == XEP80_ATARI_EOL)
			video_ram[curs] = 0x20;
		AdvanceCursor(prev);
		if (xpos == rmargin)
			return;
		if (tab_stops(xpos))
			return;
	}
}
