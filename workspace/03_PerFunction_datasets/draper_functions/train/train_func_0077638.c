snd_soc_runtime_deactivate(struct snd_soc_pcm_runtime *rtd, int stream)
{
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int i;

	lockdep_assert_held(&rtd->pcm_mutex);

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		cpu_dai->playback_active--;
		for (i = 0; i < rtd->num_codecs; i++)
			rtd->codec_dais[i]->playback_active--;
	} else {
		cpu_dai->capture_active--;
		for (i = 0; i < rtd->num_codecs; i++)
			rtd->codec_dais[i]->capture_active--;
	}

	cpu_dai->active--;
	cpu_dai->component->active--;
	for (i = 0; i < rtd->num_codecs; i++) {
		rtd->codec_dais[i]->component->active--;
		rtd->codec_dais[i]->active--;
	}
}
