route_transfer(struct snd_pcm_plugin *plugin,
					const struct snd_pcm_plugin_channel *src_channels,
					struct snd_pcm_plugin_channel *dst_channels,
					snd_pcm_uframes_t frames)
{
	int nsrcs, ndsts, dst;
	struct snd_pcm_plugin_channel *dvp;
	snd_pcm_format_t format;

	if (snd_BUG_ON(!plugin || !src_channels || !dst_channels))
		return -ENXIO;
	if (frames == 0)
		return 0;

	nsrcs = plugin->src_format.channels;
	ndsts = plugin->dst_format.channels;

	format = plugin->dst_format.format;
	dvp = dst_channels;
	if (nsrcs <= 1) {

		for (dst = 0; dst < ndsts; ++dst) {
			copy_area(src_channels, dvp, frames, format);
			dvp++;
		}
		return frames;
	}

	for (dst = 0; dst < ndsts && dst < nsrcs; ++dst) {
		copy_area(src_channels, dvp, frames, format);
		dvp++;
		src_channels++;
	}
	if (dst < ndsts)
		zero_areas(dvp, ndsts - dst, frames, format);
	return frames;
}
