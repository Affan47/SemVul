snd_ali_mixer(struct snd_ali *codec)
{
	struct snd_ac97_template ac97;
	unsigned int idx;
	int i, err;
	static struct snd_ac97_bus_ops ops = {
		.write = snd_ali_codec_write,
		.read = snd_ali_codec_read,
	};

	err = snd_ac97_bus(codec->card, 0, &ops, codec, &codec->ac97_bus);
	if (err < 0)
		return err;

	memset(&ac97, 0, sizeof(ac97));
	ac97.private_data = codec;

	for (i = 0; i < codec->num_of_codecs; i++) {
		ac97.num = i;
		err = snd_ac97_mixer(codec->ac97_bus, &ac97, &codec->ac97[i]);
		if (err < 0) {
			dev_err(codec->card->dev,
				   "ali mixer %d creating error.\n", i);
			if (i == 0)
				return err;
			codec->num_of_codecs = 1;
			break;
		}
	}

	if (codec->spdif_support) {
		for (idx = 0; idx < ARRAY_SIZE(snd_ali5451_mixer_spdif); idx++) {
			err = snd_ctl_add(codec->card,
					  snd_ctl_new1(&snd_ali5451_mixer_spdif[idx], codec));
			if (err < 0)
				return err;
		}
	}
	return 0;
}
