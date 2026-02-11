snd_pcm_plugin_build_mulaw(struct snd_pcm_substream *plug,
			       struct snd_pcm_plugin_format *src_format,
			       struct snd_pcm_plugin_format *dst_format,
			       struct snd_pcm_plugin **r_plugin)
{
	int err;
	struct mulaw_priv *data;
	struct snd_pcm_plugin *plugin;
	struct snd_pcm_plugin_format *format;
	mulaw_f func;

	if (snd_BUG_ON(!r_plugin))
		return -ENXIO;
	*r_plugin = NULL;

	if (snd_BUG_ON(src_format->rate != dst_format->rate))
		return -ENXIO;
	if (snd_BUG_ON(src_format->channels != dst_format->channels))
		return -ENXIO;

	if (dst_format->format == SNDRV_PCM_FORMAT_MU_LAW) {
		format = src_format;
		func = mulaw_encode;
	}
	else if (src_format->format == SNDRV_PCM_FORMAT_MU_LAW) {
		format = dst_format;
		func = mulaw_decode;
	}
	else {
		snd_BUG();
		return -EINVAL;
	}
	if (snd_BUG_ON(!snd_pcm_format_linear(format->format)))
		return -ENXIO;

	err = snd_pcm_plugin_build(plug, "Mu-Law<->linear conversion",
				   src_format, dst_format,
				   sizeof(struct mulaw_priv), &plugin);
	if (err < 0)
		return err;
	data = (struct mulaw_priv *)plugin->extra_data;
	data->func = func;
	init_data(data, format->format);
	plugin->transfer = mulaw_transfer;
	*r_plugin = plugin;
	return 0;
}
