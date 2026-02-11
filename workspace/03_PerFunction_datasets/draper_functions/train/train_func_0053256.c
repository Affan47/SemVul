adm8211_hw_reset(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	u32 reg, tmp;
	int timeout = 100;


	ADM8211_CSR_WRITE(FRCTL, 0);


	tmp = ADM8211_CSR_READ(PAR);
	ADM8211_CSR_WRITE(PAR, ADM8211_PAR_SWR);

	while ((ADM8211_CSR_READ(PAR) & ADM8211_PAR_SWR) && timeout--)
		msleep(50);

	if (timeout <= 0)
		return -ETIMEDOUT;

	ADM8211_CSR_WRITE(PAR, tmp);

	if (priv->pdev->revision == ADM8211_REV_BA &&
	    (priv->transceiver_type == ADM8211_RFMD2958_RF3000_CONTROL_POWER ||
	     priv->transceiver_type == ADM8211_RFMD2958)) {
		reg = ADM8211_CSR_READ(CSR_TEST1);
		reg |= (1 << 4) | (1 << 5);
		ADM8211_CSR_WRITE(CSR_TEST1, reg);
	} else if (priv->pdev->revision == ADM8211_REV_CA) {
		reg = ADM8211_CSR_READ(CSR_TEST1);
		reg &= ~((1 << 4) | (1 << 5));
		ADM8211_CSR_WRITE(CSR_TEST1, reg);
	}

	ADM8211_CSR_WRITE(FRCTL, 0);

	reg = ADM8211_CSR_READ(CSR_TEST0);
	reg |= ADM8211_CSR_TEST0_EPRLD;
	ADM8211_CSR_WRITE(CSR_TEST0, reg);

	adm8211_clear_sram(dev);

	return 0;
}
