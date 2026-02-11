ad1848_mixer_reset(ad1848_info * devc)
{
	int i;
	char name[32];
	unsigned long flags;

	devc->mix_devices = &(ad1848_mix_devices[0]);

	sprintf(name, "%s_%d", devc->chip_name, nr_ad1848_devs);

	for (i = 0; i < 32; i++)
		devc->mixer_reroute[i] = i;

	devc->supported_rec_devices = MODE1_REC_DEVICES;

	switch (devc->model)
	{
		case MD_4231:
		case MD_4231A:
		case MD_1845:
		case MD_1845_SSCAPE:
			devc->supported_devices = MODE2_MIXER_DEVICES;
			break;

		case MD_C930:
			devc->supported_devices = C930_MIXER_DEVICES;
			devc->mix_devices = &(c930_mix_devices[0]);
			break;

		case MD_IWAVE:
			devc->supported_devices = MODE3_MIXER_DEVICES;
			devc->mix_devices = &(iwave_mix_devices[0]);
			break;

		case MD_42xB:
		case MD_4239:
			devc->mix_devices = &(cs42xb_mix_devices[0]);
			devc->supported_devices = MODE3_MIXER_DEVICES;
			break;
		case MD_4232:
		case MD_4235:
		case MD_4236:
			devc->supported_devices = MODE3_MIXER_DEVICES;
			break;

		case MD_1848:
			if (soundpro) {
				devc->supported_devices = SPRO_MIXER_DEVICES;
				devc->supported_rec_devices = SPRO_REC_DEVICES;
				devc->mix_devices = &(spro_mix_devices[0]);
				break;
			}

		default:
			devc->supported_devices = MODE1_MIXER_DEVICES;
	}

	devc->orig_devices = devc->supported_devices;
	devc->orig_rec_devices = devc->supported_rec_devices;

	devc->levels = load_mixer_volumes(name, default_mixer_levels, 1);

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
	{
		if (devc->supported_devices & (1 << i))
			ad1848_mixer_set(devc, i, devc->levels[i]);
	}

	ad1848_set_recmask(devc, SOUND_MASK_MIC);

	devc->mixer_output_port = devc->levels[31] | AUDIO_HEADPHONE | AUDIO_LINE_OUT;

	spin_lock_irqsave(&devc->lock,flags);
	if (!soundpro) {
		if (devc->mixer_output_port & AUDIO_SPEAKER)
			ad_write(devc, 26, ad_read(devc, 26) & ~0x40);
		else
			ad_write(devc, 26, ad_read(devc, 26) | 0x40);
	} else {


		ad_write(devc, 16, 0x60);
	}
	spin_unlock_irqrestore(&devc->lock,flags);
}
