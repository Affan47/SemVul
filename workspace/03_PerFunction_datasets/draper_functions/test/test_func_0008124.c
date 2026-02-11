snd_pcm_multi_hw_free(snd_pcm_t *pcm)
{
	snd_pcm_multi_t *multi = pcm->private_data;
	unsigned int i;
	int err = 0;
	for (i = 0; i < multi->slaves_count; ++i) {
		snd_pcm_t *slave = multi->slaves[i].pcm;
		int e = snd_pcm_hw_free(slave);
		if (e < 0)
			err = e;
		if (!multi->slaves[i].linked)
			continue;
		e = snd_pcm_unlink(slave);
		if (e < 0)
			err = e;
		multi->slaves[i].linked = NULL;
	}
	return err;
}
