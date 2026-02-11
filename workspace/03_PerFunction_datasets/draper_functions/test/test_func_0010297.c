gf_mixer_add_input(GF_AudioMixer *am, GF_AudioInterface *src)
{
	MixerInput *in;
	if (gf_mixer_is_src_present(am, src)) return;
	gf_mixer_lock(am, 1);
	GF_SAFEALLOC(in, MixerInput);
	in->src = src;
	gf_list_add(am->sources, in);
	am->must_reconfig = 1;
	am->isEmpty = 0;
	gf_mixer_lock(am, 0);
}
