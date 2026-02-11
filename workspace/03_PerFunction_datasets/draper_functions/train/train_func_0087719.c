gf_mixer_is_src_present(GF_AudioMixer *am, GF_AudioInterface *ifce)
{
	MixerInput *in;
	u32 i = 0;
	while ((in = (MixerInput *)gf_list_enum(am->sources, &i))) {
		if (in->src == ifce) return 1;
	}
	return 0;
}
