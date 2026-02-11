uda134x_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				  int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct uda134x_priv *uda134x = snd_soc_codec_get_drvdata(codec);

	pr_debug("%s clk_id: %d, freq: %u, dir: %d\n", __func__,
		 clk_id, freq, dir);


	if ((freq >= (256 * 8000)) && (freq <= (512 * 48000))) {
		uda134x->sysclk = freq;
		return 0;
	}

	printk(KERN_ERR "%s unsupported sysclk\n", __func__);
	return -EINVAL;
}
