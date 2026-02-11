snd_pcm_mmap_emul_sw_params(snd_pcm_t *pcm,
				       snd_pcm_sw_params_t *params)
{
	mmap_emul_t *map = pcm->private_data;
	int err;

	if (!map->mmap_emul)
		return snd_pcm_generic_sw_params(pcm, params);

	map->start_threshold = params->start_threshold;


	params->start_threshold = pcm->boundary;
	err = snd_pcm_generic_sw_params(pcm, params);
	if (err < 0)
		return err;

	params->start_threshold = map->start_threshold;
	return err;
}
