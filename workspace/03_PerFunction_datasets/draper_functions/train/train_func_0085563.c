mp_stop(midi_player_t *mp)
{
	unsigned c;
	if(!mp)
		return;
	if(!mp->sock->control_change)
		return;
	for(c = 0; c < 16; ++c)
	{
		mp->sock->control_change(c, 120, 1);
		mp->sock->control_change(c, 121, 1);
		mp->sock->control_change(c, 123, 1);
	}
	mp->mf = NULL;
}
