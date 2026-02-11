gf_sc_ar_set_volume(GF_AudioRenderer *ar, u32 Volume)
{
	char sOpt[10];
	gf_mixer_lock(ar->mixer, 1);
	ar->volume = MIN(Volume, 100);
	if (ar->audio_out) ar->audio_out->SetVolume(ar->audio_out, ar->volume);
	sprintf(sOpt, "%d", ar->volume);
	gf_cfg_set_key(ar->user->config, "Audio", "Volume", sOpt);

	gf_mixer_lock(ar->mixer, 0);
}
