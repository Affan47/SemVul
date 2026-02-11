snd_pcm_iec958_hw_refine_cprepare(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
	snd_pcm_iec958_t *iec = pcm->private_data;
	int err;
	snd_pcm_access_mask_t access_mask = { SND_PCM_ACCBIT_SHM };
	err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_ACCESS,
					 &access_mask);
	if (err < 0)
		return err;
	if (iec->sformat == SND_PCM_FORMAT_IEC958_SUBFRAME_LE ||
	    iec->sformat == SND_PCM_FORMAT_IEC958_SUBFRAME_BE) {
		snd_pcm_format_mask_t format_mask = { SND_PCM_FMTBIT_LINEAR };
		err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_FORMAT,
						 &format_mask);
	} else {
		snd_pcm_format_mask_t format_mask = {
			{ (1U << SND_PCM_FORMAT_IEC958_SUBFRAME_LE) |
			  (1U << SND_PCM_FORMAT_IEC958_SUBFRAME_BE) }
		};
		err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_FORMAT,
						 &format_mask);
	}
	if (err < 0)
		return err;
	err = _snd_pcm_hw_params_set_subformat(params, SND_PCM_SUBFORMAT_STD);
	if (err < 0)
		return err;
	params->info &= ~(SND_PCM_INFO_MMAP | SND_PCM_INFO_MMAP_VALID);
	return 0;
}
