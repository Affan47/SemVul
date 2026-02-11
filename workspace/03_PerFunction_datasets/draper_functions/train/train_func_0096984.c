snd_pcm_share_hw_refine_cchange(snd_pcm_t *pcm ATTRIBUTE_UNUSED, snd_pcm_hw_params_t *params,
					   snd_pcm_hw_params_t *sparams)
{
	int err;
	unsigned int links = (SND_PCM_HW_PARBIT_FORMAT |
			      SND_PCM_HW_PARBIT_SUBFORMAT |
			      SND_PCM_HW_PARBIT_RATE |
			      SND_PCM_HW_PARBIT_PERIOD_SIZE |
			      SND_PCM_HW_PARBIT_PERIOD_TIME |
			      SND_PCM_HW_PARBIT_BUFFER_SIZE |
			      SND_PCM_HW_PARBIT_BUFFER_TIME |
			      SND_PCM_HW_PARBIT_PERIODS);
	snd_pcm_access_mask_t access_mask;
	const snd_pcm_access_mask_t *saccess_mask = snd_pcm_hw_param_get_mask(sparams, SND_PCM_HW_PARAM_ACCESS);
	snd_pcm_access_mask_any(&access_mask);
	snd_pcm_access_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_INTERLEAVED);
	if (!snd_pcm_access_mask_test(saccess_mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED))
		snd_pcm_access_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED);
	if (!snd_pcm_access_mask_test(saccess_mask, SND_PCM_ACCESS_MMAP_COMPLEX) &&
	    !snd_pcm_access_mask_test(saccess_mask, SND_PCM_ACCESS_MMAP_INTERLEAVED))
		snd_pcm_access_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_COMPLEX);
	err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_ACCESS,
					 &access_mask);
	if (err < 0)
		return err;
	err = _snd_pcm_hw_params_refine(params, links, sparams);
	if (err < 0)
		return err;
	return 0;
}
