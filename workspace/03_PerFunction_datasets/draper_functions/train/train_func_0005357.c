snd_cs5535audio_capture_open(struct snd_pcm_substream *substream)
{
	int err;
	struct cs5535audio *cs5535au = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	runtime->hw = snd_cs5535audio_capture;
	runtime->hw.rates = cs5535au->ac97->rates[AC97_RATES_ADC];
	snd_pcm_limit_hw_rates(runtime);
	cs5535au->capture_substream = substream;
	runtime->private_data = &(cs5535au->dmas[CS5535AUDIO_DMA_CAPTURE]);
	if ((err = snd_pcm_hw_constraint_integer(runtime,
					 SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		return err;
	olpc_capture_open(cs5535au->ac97);
	return 0;
}
