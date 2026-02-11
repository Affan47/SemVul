pcm512x_find_sck(struct snd_soc_dai *dai,
				      unsigned long bclk_rate)
{
	struct device *dev = dai->dev;
	struct snd_soc_codec *codec = dai->codec;
	struct pcm512x_priv *pcm512x = snd_soc_codec_get_drvdata(codec);
	unsigned long sck_rate;
	int pow2;


	pow2 = 1 << fls((pcm512x_pll_max(pcm512x) - 16000000) / bclk_rate);
	for (; pow2; pow2 >>= 1) {
		sck_rate = rounddown(pcm512x_pll_max(pcm512x),
				     bclk_rate * pow2);
		if (sck_rate >= 16000000)
			break;
	}
	if (!pow2) {
		dev_err(dev, "Impossible to generate a suitable SCK\n");
		return 0;
	}

	dev_dbg(dev, "sck_rate %lu\n", sck_rate);
	return sck_rate;
}
