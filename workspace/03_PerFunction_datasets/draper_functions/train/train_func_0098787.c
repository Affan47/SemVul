prodigy192_add_controls(struct snd_ice1712 *ice)
{
	struct prodigy192_spec *spec = ice->spec;
	unsigned int i;
	int err;

	for (i = 0; i < ARRAY_SIZE(stac_controls); i++) {
		err = snd_ctl_add(ice->card,
				  snd_ctl_new1(&stac_controls[i], ice));
		if (err < 0)
			return err;
	}
	if (spec->ak4114) {

		for (i = 0; i < ARRAY_SIZE(ak4114_controls); i++) {
			err = snd_ctl_add(ice->card,
					  snd_ctl_new1(&ak4114_controls[i],
						       ice));
			if (err < 0)
				return err;
		}
		err = snd_ak4114_build(spec->ak4114,
				NULL,
				ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
		if (err < 0)
			return err;
	}
	stac9460_proc_init(ice);
	return 0;
}
