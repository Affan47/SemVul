snd_pcm_plug_change_format(snd_pcm_t *pcm, snd_pcm_t **new, snd_pcm_plug_params_t *clt, snd_pcm_plug_params_t *slv)
{
	snd_pcm_plug_t *plug = pcm->private_data;
	int err;
	snd_pcm_format_t cfmt;
	int (*f)(snd_pcm_t **_pcm, const char *name, snd_pcm_format_t sformat, snd_pcm_t *slave, int close_slave);


	if (clt->format == slv->format &&
	    clt->rate == slv->rate &&
	    clt->channels == slv->channels)
		return 0;

	if (snd_pcm_format_linear(slv->format)) {

		if (clt->rate != slv->rate ||
		    clt->channels != slv->channels)
			return 0;
		cfmt = clt->format;
		switch (clt->format) {
#ifdef BUILD_PCM_PLUGIN_MULAW
		case SND_PCM_FORMAT_MU_LAW:
			f = snd_pcm_mulaw_open;
			break;
#endif
#ifdef BUILD_PCM_PLUGIN_ALAW
		case SND_PCM_FORMAT_A_LAW:
			f = snd_pcm_alaw_open;
			break;
#endif
#ifdef BUILD_PCM_PLUGIN_ADPCM
		case SND_PCM_FORMAT_IMA_ADPCM:
			f = snd_pcm_adpcm_open;
			break;
#endif
		default:
#ifdef BUILD_PCM_PLUGIN_LFLOAT
			if (snd_pcm_format_float(clt->format))
				f = snd_pcm_lfloat_open;

			else
#endif
				f = snd_pcm_linear_open;
			break;
		}
#ifdef BUILD_PCM_PLUGIN_LFLOAT
	} else if (snd_pcm_format_float(slv->format)) {

		if (clt->format == slv->format &&
		    clt->rate == slv->rate &&
		    clt->channels == slv->channels)
			return 0;
		cfmt = clt->format;
		if (snd_pcm_format_linear(clt->format))
			f = snd_pcm_lfloat_open;
		else
			return -EINVAL;
#endif
#ifdef BUILD_PCM_NONLINEAR
	} else {
		switch (slv->format) {
#ifdef BUILD_PCM_PLUGIN_MULAW
		case SND_PCM_FORMAT_MU_LAW:
			f = snd_pcm_mulaw_open;
			break;
#endif
#ifdef BUILD_PCM_PLUGIN_ALAW
		case SND_PCM_FORMAT_A_LAW:
			f = snd_pcm_alaw_open;
			break;
#endif
#ifdef BUILD_PCM_PLUGIN_ADPCM
		case SND_PCM_FORMAT_IMA_ADPCM:
			f = snd_pcm_adpcm_open;
			break;
#endif
		default:
			return -EINVAL;
		}
		if (snd_pcm_format_linear(clt->format))
			cfmt = clt->format;
		else
			cfmt = SND_PCM_FORMAT_S16;
#endif
	}
	err = f(new, NULL, slv->format, plug->gen.slave, plug->gen.slave != plug->req_slave);
	if (err < 0)
		return err;
	slv->format = cfmt;
	slv->access = clt->access;
	return 1;
}
