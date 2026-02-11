stv6110_set_bandwidth(struct dvb_frontend *fe, u32 bandwidth)
{
	struct stv6110_priv *priv = fe->tuner_priv;
	u8 r8, ret = 0x04;
	int i;

	if ((bandwidth / 2) > 36000000)
		r8 = 31;
	else if ((bandwidth / 2) < 5000000)
		r8 = 0;
	else
		r8 = (bandwidth / 2) / 1000000 - 5;


	priv->regs[RSTV6110_CTRL3] &= ~((1 << 6) | 0x1f);
	priv->regs[RSTV6110_CTRL3] |= (r8 & 0x1f);
	stv6110_write_regs(fe, &priv->regs[RSTV6110_CTRL3], RSTV6110_CTRL3, 1);

	priv->regs[RSTV6110_STAT1] |= 0x02;
	stv6110_write_regs(fe, &priv->regs[RSTV6110_STAT1], RSTV6110_STAT1, 1);

	i = 0;

	while ((i < 10) && (ret != 0)) {
		ret = ((stv6110_read_reg(fe, RSTV6110_STAT1)) & 0x02);
		mdelay(1);
		i++;
	}


	priv->regs[RSTV6110_CTRL3] |= (1 << 6);
	stv6110_write_regs(fe, &priv->regs[RSTV6110_CTRL3], RSTV6110_CTRL3, 1);
	return 0;
}
