bcm2835_i2s_stop_clock(struct bcm2835_i2s_dev *dev)
{
	uint32_t clkreg;
	int timeout = 1000;


	regmap_update_bits(dev->clk_regmap, BCM2835_CLK_PCMCTL_REG,
			BCM2835_CLK_PASSWD_MASK | BCM2835_CLK_ENAB,
			BCM2835_CLK_PASSWD);


	while (--timeout) {
		regmap_read(dev->clk_regmap, BCM2835_CLK_PCMCTL_REG, &clkreg);
		if (!(clkreg & BCM2835_CLK_BUSY))
			break;
	}

	if (!timeout) {

		dev_err(dev->dev, "I2S clock didn't stop. Kill the clock!\n");
		regmap_update_bits(dev->clk_regmap, BCM2835_CLK_PCMCTL_REG,
			BCM2835_CLK_KILL | BCM2835_CLK_PASSWD_MASK,
			BCM2835_CLK_KILL | BCM2835_CLK_PASSWD);
	}
}
