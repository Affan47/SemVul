gf_sc_ar_mute(GF_AudioRenderer *ar, Bool mute)
{
	gf_mixer_lock(ar->mixer, 1);
	ar->mute = mute;
	if (ar->audio_out) ar->audio_out->SetVolume(ar->audio_out, mute ? 0 : ar->volume);
	gf_mixer_lock(ar->mixer, 0);
}
