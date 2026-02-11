alc5632_probe(struct snd_soc_codec *codec)
{
	struct alc5632_priv *alc5632 = snd_soc_codec_get_drvdata(codec);

	switch (alc5632->id) {
	case 0x5c:
		snd_soc_add_codec_controls(codec, alc5632_vol_snd_controls,
			ARRAY_SIZE(alc5632_vol_snd_controls));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
