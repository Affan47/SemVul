snd_pcm_meter_hw_refine_schange(snd_pcm_t *pcm ATTRIBUTE_UNUSED, snd_pcm_hw_params_t *params,
					  snd_pcm_hw_params_t *sparams)
{
	int err;
	unsigned int links = ~SND_PCM_HW_PARBIT_ACCESS;
	err = _snd_pcm_hw_params_refine(sparams, links, params);
	if (err < 0)
		return err;
	return 0;
}
