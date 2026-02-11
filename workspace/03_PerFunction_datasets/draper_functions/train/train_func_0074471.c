rtl8187_set_anaparam(struct rtl8187_priv *priv, bool rfon)
{
	u32 anaparam, anaparam2;
	u8 anaparam3, reg;

	if (!priv->is_rtl8187b) {
		if (rfon) {
			anaparam = RTL8187_RTL8225_ANAPARAM_ON;
			anaparam2 = RTL8187_RTL8225_ANAPARAM2_ON;
		} else {
			anaparam = RTL8187_RTL8225_ANAPARAM_OFF;
			anaparam2 = RTL8187_RTL8225_ANAPARAM2_OFF;
		}
	} else {
		if (rfon) {
			anaparam = RTL8187B_RTL8225_ANAPARAM_ON;
			anaparam2 = RTL8187B_RTL8225_ANAPARAM2_ON;
			anaparam3 = RTL8187B_RTL8225_ANAPARAM3_ON;
		} else {
			anaparam = RTL8187B_RTL8225_ANAPARAM_OFF;
			anaparam2 = RTL8187B_RTL8225_ANAPARAM2_OFF;
			anaparam3 = RTL8187B_RTL8225_ANAPARAM3_OFF;
		}
	}

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
	reg |= RTL818X_CONFIG3_ANAPARAM_WRITE;
	rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg);
	rtl818x_iowrite32(priv, &priv->map->ANAPARAM, anaparam);
	rtl818x_iowrite32(priv, &priv->map->ANAPARAM2, anaparam2);
	if (priv->is_rtl8187b)
		rtl818x_iowrite8(priv, &priv->map->ANAPARAM3A, anaparam3);
	reg &= ~RTL818X_CONFIG3_ANAPARAM_WRITE;
	rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
}
