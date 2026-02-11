alsa_set_volume( int percentdiff )
{
	long volume;

	alsa_get_volume();

	alsa_vol += percentdiff;
	if( alsa_vol > 100 ) alsa_vol = 100;
	if( alsa_vol < 0 ) alsa_vol = 0;

	volume = (long)((alsa_vol * (alsa_max - alsa_min) / 100.) + 0.5);

	snd_mixer_selem_set_playback_volume_all(elem, volume + alsa_min);
	snd_mixer_selem_set_playback_switch_all(elem, 1);
	muted = 0;
	mutecount = 0;

	return alsa_vol;
}
