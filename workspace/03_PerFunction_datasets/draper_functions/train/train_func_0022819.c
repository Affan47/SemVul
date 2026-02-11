wm2200_set_sysclk(struct snd_soc_codec *codec, int clk_id,
			     int source, unsigned int freq, int dir)
{
	struct wm2200_priv *wm2200 = snd_soc_codec_get_drvdata(codec);
	int fval;

	switch (clk_id) {
	case WM2200_CLK_SYSCLK:
		break;

	default:
		dev_err(codec->dev, "Unknown clock %d\n", clk_id);
		return -EINVAL;
	}

	switch (source) {
	case WM2200_CLKSRC_MCLK1:
	case WM2200_CLKSRC_MCLK2:
	case WM2200_CLKSRC_FLL:
	case WM2200_CLKSRC_BCLK1:
		break;
	default:
		dev_err(codec->dev, "Invalid source %d\n", source);
		return -EINVAL;
	}

	switch (freq) {
	case 22579200:
	case 24576000:
		fval = 2;
		break;
	default:
		dev_err(codec->dev, "Invalid clock rate: %d\n", freq);
		return -EINVAL;
	}


	snd_soc_update_bits(codec, WM2200_CLOCKING_3, WM2200_SYSCLK_FREQ_MASK |
			    WM2200_SYSCLK_SRC_MASK,
			    fval << WM2200_SYSCLK_FREQ_SHIFT | source);

	wm2200->sysclk = freq;

	return 0;
}
