sequencer_play(midi_file_t *mf, int tag, int pitch, int volume)
{
	aev_client("sequencer_play()");
	if(!midiplayer)
		return -1;

	midiplayer->pitch = pitch - (60 << 16);
	mp_select(midiplayer, mf);
	return 0;
}
