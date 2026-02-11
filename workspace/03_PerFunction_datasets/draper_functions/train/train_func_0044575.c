dai_get_widget(struct snd_soc_dai *dai, int stream)
{
	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		return dai->playback_widget;
	else
		return dai->capture_widget;
}
