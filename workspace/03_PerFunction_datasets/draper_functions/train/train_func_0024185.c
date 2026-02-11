wm8580_set_sysclk(struct snd_soc_dai *dai, int clk_id,
			     unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = dai->codec;
	struct wm8580_priv *wm8580 = snd_soc_codec_get_drvdata(codec);
	int ret, sel, sel_mask, sel_shift;

	switch (dai->driver->id) {
	case WM8580_DAI_PAIFRX:
		sel_mask = 0x3;
		sel_shift = 0;
		break;

	case WM8580_DAI_PAIFTX:
		sel_mask = 0xc;
		sel_shift = 2;
		break;

	default:
		WARN(1, "Unknown DAI driver ID\n");
		return -EINVAL;
	}

	switch (clk_id) {
	case WM8580_CLKSRC_ADCMCLK:
		if (dai->driver->id != WM8580_DAI_PAIFTX)
			return -EINVAL;
		sel = 0 << sel_shift;
		break;
	case WM8580_CLKSRC_PLLA:
		sel = 1 << sel_shift;
		break;
	case WM8580_CLKSRC_PLLB:
		sel = 2 << sel_shift;
		break;
	case WM8580_CLKSRC_MCLK:
		sel = 3 << sel_shift;
		break;
	default:
		dev_err(codec->dev, "Unknown clock %d\n", clk_id);
		return -EINVAL;
	}


	wm8580->sysclk[dai->driver->id] = freq;

	ret = snd_soc_update_bits(codec, WM8580_CLKSEL, sel_mask, sel);
	if (ret < 0)
		return ret;

	return 0;
}
