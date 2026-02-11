wm1250_ev1_set_bias_level(struct snd_soc_codec *codec,
				     enum snd_soc_bias_level level)
{
	struct wm1250_priv *wm1250 = dev_get_drvdata(codec->dev);
	int ena;

	if (wm1250)
		ena = wm1250->gpios[WM1250_EV1_GPIO_CLK_ENA].gpio;
	else
		ena = -1;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		if (ena >= 0)
			gpio_set_value_cansleep(ena, 1);
		break;

	case SND_SOC_BIAS_OFF:
		if (ena >= 0)
			gpio_set_value_cansleep(ena, 0);
		break;
	}

	return 0;
}
