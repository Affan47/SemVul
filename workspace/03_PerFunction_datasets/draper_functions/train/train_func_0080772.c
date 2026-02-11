snd_pcm_multi_drain(snd_pcm_t *pcm)
{
	snd_pcm_multi_t *multi = pcm->private_data;
	int err = 0;
	unsigned int i;
	if (multi->slaves[0].linked)
		return snd_pcm_drain(multi->slaves[0].linked);
	for (i = 0; i < multi->slaves_count; ++i) {
		if (multi->slaves[i].linked)
			continue;
		err = snd_pcm_drain(multi->slaves[i].pcm);
		if (err < 0)
			return err;
	}
	return err;
}
