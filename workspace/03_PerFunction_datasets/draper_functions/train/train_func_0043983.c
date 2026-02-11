juli_spdif_in_open(struct snd_ice1712 *ice,
				struct snd_pcm_substream *substream)
{
	struct juli_spec *spec = ice->spec;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int rate;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK ||
			!ice->is_spdif_master(ice))
		return;
	rate = snd_ak4114_external_rate(spec->ak4114);
	if (rate >= runtime->hw.rate_min && rate <= runtime->hw.rate_max) {
		runtime->hw.rate_min = rate;
		runtime->hw.rate_max = rate;
	}
}
