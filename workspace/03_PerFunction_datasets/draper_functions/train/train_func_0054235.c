snd_ice1712_capture_pro_close(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	if (PRO_RATE_RESET)
		snd_ice1712_set_pro_rate(ice, PRO_RATE_DEFAULT, 0);
	ice->capture_pro_substream = NULL;
	return 0;
}
