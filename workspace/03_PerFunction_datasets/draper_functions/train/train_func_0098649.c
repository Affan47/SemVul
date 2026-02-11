xtfpga_pcm_refill_fifo(struct xtfpga_i2s *i2s)
{
	unsigned int_status;
	unsigned i;

	regmap_read(i2s->regmap, XTFPGA_I2S_INT_STATUS,
		    &int_status);

	for (i = 0; i < 2; ++i) {
		bool tx_active = xtfpga_pcm_push_tx(i2s);

		regmap_write(i2s->regmap, XTFPGA_I2S_INT_STATUS,
			     XTFPGA_I2S_INT_VALID);
		if (tx_active)
			regmap_read(i2s->regmap, XTFPGA_I2S_INT_STATUS,
				    &int_status);

		if (!tx_active ||
		    !(int_status & XTFPGA_I2S_INT_LEVEL))
			break;


		i2s->tx_fifo_level = i2s->tx_fifo_low;
	}

	if (!(int_status & XTFPGA_I2S_INT_LEVEL))
		regmap_write(i2s->regmap, XTFPGA_I2S_INT_MASK,
			     XTFPGA_I2S_INT_VALID);
	else if (!(int_status & XTFPGA_I2S_INT_UNDERRUN))
		regmap_write(i2s->regmap, XTFPGA_I2S_INT_MASK,
			     XTFPGA_I2S_INT_UNDERRUN);

	if (!(int_status & XTFPGA_I2S_INT_UNDERRUN))
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE);
	else
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE, 0);
}
