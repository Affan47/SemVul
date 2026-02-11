snd_mixer_selem_register(snd_mixer_t *mixer,
			     struct snd_mixer_selem_regopt *options,
			     snd_mixer_class_t **classp)
{
	if (options && options->ver == 1) {
		if (options->device != NULL &&
		    (options->playback_pcm != NULL ||
		     options->capture_pcm != NULL))
			return -EINVAL;
		if (options->device == NULL &&
		    options->playback_pcm == NULL &&
		    options->capture_pcm == NULL)
			return -EINVAL;
	}
	if (options == NULL ||
	    (options->ver == 1 && options->abstract == SND_MIXER_SABSTRACT_NONE)) {
		int err = snd_mixer_simple_none_register(mixer, options, classp);
		if (err < 0)
			return err;
		if (options != NULL) {
			err = snd_mixer_attach(mixer, options->device);
			if (err < 0)
				return err;
		}
		return 0;
	} else if (options->ver == 1) {
		if (options->abstract == SND_MIXER_SABSTRACT_BASIC)
			return snd_mixer_simple_basic_register(mixer, options, classp);
	}
	return -ENXIO;
}
