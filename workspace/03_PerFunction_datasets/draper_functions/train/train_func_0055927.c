mp_open(midisock_t *ms)
{
	midi_player_t *mp = calloc(1, sizeof(midi_player_t));
	if(!mp)
		return NULL;
	mp->sock = ms;
	mp->mf = NULL;
	return mp;
}
