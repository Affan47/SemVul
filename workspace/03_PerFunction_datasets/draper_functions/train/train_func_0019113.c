snd_pcm_plug_client_size(struct snd_pcm_substream *plug, snd_pcm_uframes_t drv_frames)
{
	struct snd_pcm_plugin *plugin, *plugin_prev, *plugin_next;
	int stream;

	if (snd_BUG_ON(!plug))
		return -ENXIO;
	if (drv_frames == 0)
		return 0;
	stream = snd_pcm_plug_stream(plug);
	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		plugin = snd_pcm_plug_last(plug);
		while (plugin && drv_frames > 0) {
			plugin_prev = plugin->prev;
			if (plugin->src_frames)
				drv_frames = plugin->src_frames(plugin, drv_frames);
			plugin = plugin_prev;
		}
	} else if (stream == SNDRV_PCM_STREAM_CAPTURE) {
		plugin = snd_pcm_plug_first(plug);
		while (plugin && drv_frames > 0) {
			plugin_next = plugin->next;
			if (plugin->dst_frames)
				drv_frames = plugin->dst_frames(plugin, drv_frames);
			plugin = plugin_next;
		}
	} else
		snd_BUG();
	return drv_frames;
}
