mulaw_transfer(struct snd_pcm_plugin *plugin,
			      const struct snd_pcm_plugin_channel *src_channels,
			      struct snd_pcm_plugin_channel *dst_channels,
			      snd_pcm_uframes_t frames)
{
	struct mulaw_priv *data;

	if (snd_BUG_ON(!plugin || !src_channels || !dst_channels))
		return -ENXIO;
	if (frames == 0)
		return 0;
#ifdef CONFIG_SND_DEBUG
	{
		unsigned int channel;
		for (channel = 0; channel < plugin->src_format.channels; channel++) {
			if (snd_BUG_ON(src_channels[channel].area.first % 8 ||
				       src_channels[channel].area.step % 8))
				return -ENXIO;
			if (snd_BUG_ON(dst_channels[channel].area.first % 8 ||
				       dst_channels[channel].area.step % 8))
				return -ENXIO;
		}
	}
#endif
	data = (struct mulaw_priv *)plugin->extra_data;
	data->func(plugin, src_channels, dst_channels, frames);
	return frames;
}
