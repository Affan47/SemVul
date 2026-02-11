mt2060_calibrate(struct mt2060_priv *priv)
{
	u8 b = 0;
	int i = 0;

	if (mt2060_writeregs(priv,mt2060_config1,sizeof(mt2060_config1)))
		return;
	if (mt2060_writeregs(priv,mt2060_config2,sizeof(mt2060_config2)))
		return;


	mt2060_writereg(priv, REG_VGAG, (priv->cfg->clock_out << 6) | 0x30);

	do {
		b |= (1 << 6);
		mt2060_writereg(priv, REG_LO2C1,b);
		msleep(20);

		if (i == 0) {
			b |= (1 << 7);
			mt2060_writereg(priv, REG_LO2C1,b);
			b &= ~(1 << 7);
			msleep(20);
		}

		b &= ~(1 << 6);
		mt2060_writereg(priv, REG_LO2C1,b);

		msleep(20);
		i++;
	} while (i < 9);

	i = 0;
	while (i++ < 10 && mt2060_readreg(priv, REG_MISC_STAT, &b) == 0 && (b & (1 << 6)) == 0)
		msleep(20);

	if (i <= 10) {
		mt2060_readreg(priv, REG_FM_FREQ, &priv->fmfreq);
		dprintk("calibration was successful: %d", (int)priv->fmfreq);
	} else
		dprintk("FMCAL timed out");
}
