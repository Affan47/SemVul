configure_clock(struct snd_soc_codec *codec)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);
	struct wm8994_priv *wm8994 = snd_soc_codec_get_drvdata(codec);
	int change, new;


	configure_aif_clock(codec, 0);
	configure_aif_clock(codec, 1);


	if (wm8994->aifclk[0] == wm8994->aifclk[1]) {
		wm8958_micd_set_rate(codec);
		return 0;
	}

	if (wm8994->aifclk[0] < wm8994->aifclk[1])
		new = WM8994_SYSCLK_SRC;
	else
		new = 0;

	change = snd_soc_update_bits(codec, WM8994_CLOCKING_1,
				     WM8994_SYSCLK_SRC, new);
	if (change)
		snd_soc_dapm_sync(dapm);

	wm8958_micd_set_rate(codec);

	return 0;
}
