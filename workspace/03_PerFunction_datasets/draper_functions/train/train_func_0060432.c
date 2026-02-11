check_access_mask(snd_pcm_hw_params_t *src,
			     snd_pcm_hw_params_t *dst)
{
	const snd_pcm_access_mask_t *mask;
	snd_pcm_access_mask_t smask;

	mask = snd_pcm_hw_param_get_mask(src, SND_PCM_HW_PARAM_ACCESS);
	snd_mask_none(&smask);
	if (snd_pcm_access_mask_test(mask, SND_PCM_ACCESS_RW_INTERLEAVED) ||
	    snd_pcm_access_mask_test(mask, SND_PCM_ACCESS_MMAP_INTERLEAVED)) {
		snd_pcm_access_mask_set(&smask,
					SND_PCM_ACCESS_RW_INTERLEAVED);
		snd_pcm_access_mask_set(&smask,
					SND_PCM_ACCESS_MMAP_INTERLEAVED);
	}
	if (snd_pcm_access_mask_test(mask, SND_PCM_ACCESS_RW_NONINTERLEAVED) ||
	    snd_pcm_access_mask_test(mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED))  {
		snd_pcm_access_mask_set(&smask,
					SND_PCM_ACCESS_RW_NONINTERLEAVED);
		snd_pcm_access_mask_set(&smask,
					SND_PCM_ACCESS_MMAP_NONINTERLEAVED);
	}
	if (snd_pcm_access_mask_test(mask, SND_PCM_ACCESS_MMAP_COMPLEX))
		snd_pcm_access_mask_set(&smask,
					SND_PCM_ACCESS_MMAP_COMPLEX);

	return _snd_pcm_hw_param_set_mask(dst, SND_PCM_HW_PARAM_ACCESS, &smask);
}
