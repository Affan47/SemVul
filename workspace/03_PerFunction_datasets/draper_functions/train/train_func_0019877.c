soc_pcm_init_runtime_hw(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_pcm_hardware *hw = &runtime->hw;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai_driver *cpu_dai_drv = rtd->cpu_dai->driver;
	struct snd_soc_dai_driver *codec_dai_drv;
	struct snd_soc_pcm_stream *codec_stream;
	struct snd_soc_pcm_stream *cpu_stream;
	unsigned int chan_min = 0, chan_max = UINT_MAX;
	unsigned int rate_min = 0, rate_max = UINT_MAX;
	unsigned int rates = UINT_MAX;
	u64 formats = ULLONG_MAX;
	int i;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cpu_stream = &cpu_dai_drv->playback;
	else
		cpu_stream = &cpu_dai_drv->capture;


	for (i = 0; i < rtd->num_codecs; i++) {


		if (!snd_soc_dai_stream_valid(rtd->codec_dais[i],
					      substream->stream))
			continue;

		codec_dai_drv = rtd->codec_dais[i]->driver;
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			codec_stream = &codec_dai_drv->playback;
		else
			codec_stream = &codec_dai_drv->capture;
		chan_min = max(chan_min, codec_stream->channels_min);
		chan_max = min(chan_max, codec_stream->channels_max);
		rate_min = max(rate_min, codec_stream->rate_min);
		rate_max = min_not_zero(rate_max, codec_stream->rate_max);
		formats &= codec_stream->formats;
		rates = snd_pcm_rate_mask_intersect(codec_stream->rates, rates);
	}


	if (rtd->num_codecs > 1) {
		chan_min = cpu_stream->channels_min;
		chan_max = cpu_stream->channels_max;
	}

	hw->channels_min = max(chan_min, cpu_stream->channels_min);
	hw->channels_max = min(chan_max, cpu_stream->channels_max);
	if (hw->formats)
		hw->formats &= formats & cpu_stream->formats;
	else
		hw->formats = formats & cpu_stream->formats;
	hw->rates = snd_pcm_rate_mask_intersect(rates, cpu_stream->rates);

	snd_pcm_limit_hw_rates(runtime);

	hw->rate_min = max(hw->rate_min, cpu_stream->rate_min);
	hw->rate_min = max(hw->rate_min, rate_min);
	hw->rate_max = min_not_zero(hw->rate_max, cpu_stream->rate_max);
	hw->rate_max = min_not_zero(hw->rate_max, rate_max);
}
