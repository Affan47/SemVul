snd_hdspm_create_controls(struct snd_card *card,
					struct hdspm *hdspm)
{
	unsigned int idx, limit;
	int err;
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_new *list = NULL;

	switch (hdspm->io_type) {
	case MADI:
		list = snd_hdspm_controls_madi;
		limit = ARRAY_SIZE(snd_hdspm_controls_madi);
		break;
	case MADIface:
		list = snd_hdspm_controls_madiface;
		limit = ARRAY_SIZE(snd_hdspm_controls_madiface);
		break;
	case AIO:
		list = snd_hdspm_controls_aio;
		limit = ARRAY_SIZE(snd_hdspm_controls_aio);
		break;
	case RayDAT:
		list = snd_hdspm_controls_raydat;
		limit = ARRAY_SIZE(snd_hdspm_controls_raydat);
		break;
	case AES32:
		list = snd_hdspm_controls_aes32;
		limit = ARRAY_SIZE(snd_hdspm_controls_aes32);
		break;
	}

	if (NULL != list) {
		for (idx = 0; idx < limit; idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&list[idx], hdspm));
			if (err < 0)
				return err;
		}
	}


	snd_hdspm_playback_mixer.name = "Chn";
	if (hdspm->system_sample_rate >= 128000) {
		limit = hdspm->qs_out_channels;
	} else if (hdspm->system_sample_rate >= 64000) {
		limit = hdspm->ds_out_channels;
	} else {
		limit = hdspm->ss_out_channels;
	}
	for (idx = 0; idx < limit; ++idx) {
		snd_hdspm_playback_mixer.index = idx + 1;
		kctl = snd_ctl_new1(&snd_hdspm_playback_mixer, hdspm);
		err = snd_ctl_add(card, kctl);
		if (err < 0)
			return err;
		hdspm->playback_mixer_ctls[idx] = kctl;
	}


	if (hdspm->tco) {

		list = snd_hdspm_controls_tco;
		limit = ARRAY_SIZE(snd_hdspm_controls_tco);
		for (idx = 0; idx < limit; idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&list[idx], hdspm));
			if (err < 0)
				return err;
		}
	}

	return 0;
}
