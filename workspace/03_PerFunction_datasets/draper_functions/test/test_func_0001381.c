rtl8225z2_rf_set_tx_power(struct ieee80211_hw *dev, int channel)
{
	struct rtl8187_priv *priv = dev->priv;
	u8 cck_power, ofdm_power;
	const u8 *tmp;
	u32 reg;
	int i;

	cck_power = priv->channels[channel - 1].hw_value & 0xF;
	ofdm_power = priv->channels[channel - 1].hw_value >> 4;

	cck_power = min(cck_power, (u8)15);
	cck_power += priv->txpwr_base & 0xF;
	cck_power = min(cck_power, (u8)35);

	if (ofdm_power > (u8)15)
		ofdm_power = 25;
	else
		ofdm_power += 10;
	ofdm_power += priv->txpwr_base >> 4;
	ofdm_power = min(ofdm_power, (u8)35);

	if (channel == 14)
		tmp = rtl8225z2_tx_power_cck_ch14;
	else
		tmp = rtl8225z2_tx_power_cck;

	for (i = 0; i < 8; i++)
		rtl8225_write_phy_cck(dev, 0x44 + i, *tmp++);

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_CCK,
			 rtl8225z2_tx_gain_cck_ofdm[cck_power]);
	msleep(1);


	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3,
			reg | RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_iowrite32(priv, &priv->map->ANAPARAM2,
			  RTL8187_RTL8225_ANAPARAM2_ON);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3,
			reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	rtl8225_write_phy_ofdm(dev, 2, 0x42);
	rtl8225_write_phy_ofdm(dev, 5, 0x00);
	rtl8225_write_phy_ofdm(dev, 6, 0x40);
	rtl8225_write_phy_ofdm(dev, 7, 0x00);
	rtl8225_write_phy_ofdm(dev, 8, 0x40);

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_OFDM,
			 rtl8225z2_tx_gain_cck_ofdm[ofdm_power]);
	msleep(1);
}
