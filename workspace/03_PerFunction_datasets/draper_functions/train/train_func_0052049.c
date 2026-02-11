gf_mixer_set_config(GF_AudioMixer *am, u32 outSR, u32 outCH, u32 outBPS, u32 outChCfg)
{
	if ((am->bits_per_sample == outBPS) && (am->nb_channels == outCH)
		&& (am->sample_rate==outSR) && (am->channel_cfg == outChCfg)) return;

	gf_mixer_lock(am, 1);
	am->bits_per_sample = outBPS;
	if (!am->force_channel_out) am->nb_channels = outCH;
	if (get_best_samplerate(am, &outSR, &outCH, &outBPS) == GF_OK) {
		am->sample_rate = outSR;
		if (outCH>2) am->channel_cfg = outChCfg;
		else if (outCH==2) am->channel_cfg = GF_AUDIO_CH_FRONT_LEFT | GF_AUDIO_CH_FRONT_RIGHT;
		else am->channel_cfg = GF_AUDIO_CH_FRONT_LEFT;
	}

	if (am->ar)	am->ar->need_reconfig = 1;
	gf_mixer_lock(am, 0);
}
