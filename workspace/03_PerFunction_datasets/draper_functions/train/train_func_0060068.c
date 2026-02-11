snd_vt1724_playback_spdif_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	if (!ice->force_pdma4)
		update_spdif_rate(ice, substream->runtime->rate);
	return snd_vt1724_pcm_prepare(substream);
}
