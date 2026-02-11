xtfpga_i2s_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct xtfpga_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned srate = params_rate(params);
	unsigned channels = params_channels(params);
	unsigned period_size = params_period_size(params);
	unsigned sample_size = snd_pcm_format_width(params_format(params));
	unsigned freq, ratio, level;
	int err;

	regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
			   XTFPGA_I2S_CONFIG_RES_MASK,
			   sample_size << XTFPGA_I2S_CONFIG_RES_BASE);

	freq = 256 * srate;
	err = clk_set_rate(i2s->clk, freq);
	if (err < 0)
		return err;


	ratio = (freq - (srate * sample_size * 8)) /
		(srate * sample_size * 4);

	regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
			   XTFPGA_I2S_CONFIG_RATIO_MASK,
			   ratio << XTFPGA_I2S_CONFIG_RATIO_BASE);

	i2s->tx_fifo_low = XTFPGA_I2S_FIFO_SIZE / 2;


	for (level = 1;
	     i2s->tx_fifo_low / 2 >= period_size * 2 &&
	     level < (XTFPGA_I2S_CONFIG_LEVEL_MASK >>
		      XTFPGA_I2S_CONFIG_LEVEL_BASE); ++level)
		i2s->tx_fifo_low /= 2;

	i2s->tx_fifo_high = 2 * i2s->tx_fifo_low;

	regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
			   XTFPGA_I2S_CONFIG_LEVEL_MASK,
			   level << XTFPGA_I2S_CONFIG_LEVEL_BASE);

	dev_dbg(i2s->dev,
		"%s srate: %u, channels: %u, sample_size: %u, period_size: %u\n",
		__func__, srate, channels, sample_size, period_size);
	dev_dbg(i2s->dev, "%s freq: %u, ratio: %u, level: %u\n",
		__func__, freq, ratio, level);

	return 0;
}
