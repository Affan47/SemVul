wm_cd_pause( void )
{
	static int paused_pos;

	if (cur_cdmode == WM_CDM_EJECTED)
		return;

	switch (cur_cdmode) {
	case WM_CDM_PLAYING:
		cur_cdmode = WM_CDM_PAUSED;
		(drive.pause)(&drive);
                paused_pos = cur_pos_rel;
		break;

	case WM_CDM_PAUSED:
		cur_cdmode = WM_CDM_PLAYING;

		if ((drive.resume)(&drive))
			wm_cd_play(cur_track, paused_pos,
				playlist[cur_listno-1].end);
	default:
		break;
	}
}
