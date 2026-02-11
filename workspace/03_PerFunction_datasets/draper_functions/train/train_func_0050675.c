play_next_entry( int forward )
{
	if (cd == NULL)
		return;
	if (playlist != NULL && playlist[cur_listno].start)
	{
		wm_cd_play(playlist[cur_listno].start, 0,
			playlist[cur_listno].end);
		cur_listno++;
	}
	else
		wm_cd_stop();
}
