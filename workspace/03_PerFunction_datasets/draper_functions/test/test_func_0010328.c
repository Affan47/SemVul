wm8974_set_bias_level(struct snd_soc_codec *codec,
	enum snd_soc_bias_level level)
{
	u16 power1 = snd_soc_read(codec, WM8974_POWER1) & ~0x3;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		power1 |= 0x1;
		snd_soc_write(codec, WM8974_POWER1, power1);
		break;

	case SND_SOC_BIAS_STANDBY:
		power1 |= WM8974_POWER1_BIASEN | WM8974_POWER1_BUFIOEN;

		if (snd_soc_codec_get_bias_level(codec) == SND_SOC_BIAS_OFF) {
			regcache_sync(dev_get_regmap(codec->dev, NULL));


			snd_soc_write(codec, WM8974_POWER1, power1 | 0x3);
			mdelay(100);
		}

		power1 |= 0x2;
		snd_soc_write(codec, WM8974_POWER1, power1);
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_write(codec, WM8974_POWER1, 0);
		snd_soc_write(codec, WM8974_POWER2, 0);
		snd_soc_write(codec, WM8974_POWER3, 0);
		break;
	}

	return 0;
}
