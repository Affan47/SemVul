wm8960_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
		int source, unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct wm8960_priv *wm8960 = snd_soc_codec_get_drvdata(codec);

	wm8960->freq_in = freq_in;

	if (pll_id == WM8960_SYSCLK_AUTO)
		return 0;

	return wm8960_set_pll(codec, freq_in, freq_out);
}
