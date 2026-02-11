snd_pcm_multi_link(snd_pcm_t *pcm1, snd_pcm_t *pcm2)
{
	snd_pcm_multi_t *multi = pcm1->private_data;
	if (multi->slaves[0].pcm->fast_ops->link)
		return multi->slaves[0].pcm->fast_ops->link(multi->slaves[0].pcm, pcm2);
	return -ENOSYS;
}
