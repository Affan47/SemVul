snd_pcm_plugin_build_rate(struct snd_pcm_substream *plug,
			      struct snd_pcm_plugin_format *src_format,
			      struct snd_pcm_plugin_format *dst_format,
			      struct snd_pcm_plugin **r_plugin)
{
	int err;
	struct rate_priv *data;
	struct snd_pcm_plugin *plugin;

	if (snd_BUG_ON(!r_plugin))
		return -ENXIO;
	*r_plugin = NULL;

	if (snd_BUG_ON(src_format->channels != dst_format->channels))
		return -ENXIO;
	if (snd_BUG_ON(src_format->channels <= 0))
		return -ENXIO;
	if (snd_BUG_ON(src_format->format != SNDRV_PCM_FORMAT_S16))
		return -ENXIO;
	if (snd_BUG_ON(dst_format->format != SNDRV_PCM_FORMAT_S16))
		return -ENXIO;
	if (snd_BUG_ON(src_format->rate == dst_format->rate))
		return -ENXIO;

	err = snd_pcm_plugin_build(plug, "rate conversion",
				   src_format, dst_format,
				   sizeof(struct rate_priv) +
				   src_format->channels * sizeof(struct rate_channel),
				   &plugin);
	if (err < 0)
		return err;
	data = (struct rate_priv *)plugin->extra_data;
	if (src_format->rate < dst_format->rate) {
		data->pitch = ((src_format->rate << SHIFT) + (dst_format->rate >> 1)) / dst_format->rate;
		data->func = resample_expand;
	} else {
		data->pitch = ((dst_format->rate << SHIFT) + (src_format->rate >> 1)) / src_format->rate;
		data->func = resample_shrink;
	}
	data->pos = 0;
	rate_init(plugin);
	data->old_src_frames = data->old_dst_frames = 0;
	plugin->transfer = rate_transfer;
	plugin->src_frames = rate_src_frames;
	plugin->dst_frames = rate_dst_frames;
	plugin->action = rate_action;
	*r_plugin = plugin;
	return 0;
}
