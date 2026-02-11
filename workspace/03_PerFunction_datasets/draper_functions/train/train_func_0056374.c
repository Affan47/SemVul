savestate_dorewind (int pos)
{
	rewindmode = pos;
	if (pos < 0)
		pos = replaycounter - 1;
	if (canrewind (pos)) {
		savestate_state = STATE_DOREWIND;
		write_log (_T("dorewind %d (%010d/%03d) -> %d\n"), replaycounter - 1, hsync_counter, vsync_counter, pos);
		return 1;
	}
	return 0;
}
