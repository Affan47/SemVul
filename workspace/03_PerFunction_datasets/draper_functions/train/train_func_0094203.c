encx24j600_update_phcon1(struct encx24j600_priv *priv)
{
	u16 phcon1 = encx24j600_read_phy(priv, PHCON1);
	if (priv->autoneg == AUTONEG_ENABLE) {
		phcon1 |= ANEN | RENEG;
	} else {
		phcon1 &= ~ANEN;
		if (priv->speed == SPEED_100)
			phcon1 |= SPD100;
		else
			phcon1 &= ~SPD100;

		if (priv->full_duplex)
			phcon1 |= PFULDPX;
		else
			phcon1 &= ~PFULDPX;
	}
	encx24j600_write_phy(priv, PHCON1, phcon1);
}
