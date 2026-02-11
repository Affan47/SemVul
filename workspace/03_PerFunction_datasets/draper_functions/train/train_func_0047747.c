bcm_sf2_arl_search_wait(struct bcm_sf2_priv *priv)
{
	unsigned timeout = 1000;
	u32 reg;

	do {
		reg = core_readl(priv, CORE_ARLA_SRCH_CTL);
		if (!(reg & ARLA_SRCH_STDN))
			return 0;

		if (reg & ARLA_SRCH_VLID)
			return 0;

		usleep_range(1000, 2000);
	} while (timeout--);

	return -ETIMEDOUT;
}
