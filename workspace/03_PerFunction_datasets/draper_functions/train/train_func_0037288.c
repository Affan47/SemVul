snd_pcm_multi_pause(snd_pcm_t *pcm, int enable)
{
	snd_pcm_multi_t *multi = pcm->private_data;
	int err = 0;
	unsigned int i;
	if (multi->slaves[0].linked)
		return snd_pcm_pause(multi->slaves[0].linked, enable);
	for (i = 0; i < multi->slaves_count; ++i) {
		if (multi->slaves[i].linked)
			continue;
		err = snd_pcm_pause(multi->slaves[i].pcm, enable);
		if (err < 0)
			return err;
	}
	return err;
}
