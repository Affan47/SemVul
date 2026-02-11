rtl8xxxu_identify_chip(struct rtl8xxxu_priv *priv)
{
	struct device *dev = &priv->udev->dev;
	u32 val32, bonding;
	u16 val16;

	val32 = rtl8xxxu_read32(priv, REG_SYS_CFG);
	priv->chip_cut = (val32 & SYS_CFG_CHIP_VERSION_MASK) >>
		SYS_CFG_CHIP_VERSION_SHIFT;
	if (val32 & SYS_CFG_TRP_VAUX_EN) {
		dev_info(dev, "Unsupported test chip\n");
		return -ENOTSUPP;
	}

	if (val32 & SYS_CFG_BT_FUNC) {
		sprintf(priv->chip_name, "8723AU");
		priv->rf_paths = 1;
		priv->rx_paths = 1;
		priv->tx_paths = 1;
		priv->rtlchip = 0x8723a;

		val32 = rtl8xxxu_read32(priv, REG_MULTI_FUNC_CTRL);
		if (val32 & MULTI_WIFI_FUNC_EN)
			priv->has_wifi = 1;
		if (val32 & MULTI_BT_FUNC_EN)
			priv->has_bluetooth = 1;
		if (val32 & MULTI_GPS_FUNC_EN)
			priv->has_gps = 1;
	} else if (val32 & SYS_CFG_TYPE_ID) {
		bonding = rtl8xxxu_read32(priv, REG_HPON_FSM);
		bonding &= HPON_FSM_BONDING_MASK;
		if (bonding == HPON_FSM_BONDING_1T2R) {
			sprintf(priv->chip_name, "8191CU");
			priv->rf_paths = 2;
			priv->rx_paths = 2;
			priv->tx_paths = 1;
			priv->rtlchip = 0x8191c;
		} else {
			sprintf(priv->chip_name, "8192CU");
			priv->rf_paths = 2;
			priv->rx_paths = 2;
			priv->tx_paths = 2;
			priv->rtlchip = 0x8192c;
		}
		priv->has_wifi = 1;
	} else {
		sprintf(priv->chip_name, "8188CU");
		priv->rf_paths = 1;
		priv->rx_paths = 1;
		priv->tx_paths = 1;
		priv->rtlchip = 0x8188c;
		priv->has_wifi = 1;
	}

	if (val32 & SYS_CFG_VENDOR_ID)
		priv->vendor_umc = 1;

	val32 = rtl8xxxu_read32(priv, REG_GPIO_OUTSTS);
	priv->rom_rev = (val32 & GPIO_RF_RL_ID) >> 28;

	val16 = rtl8xxxu_read16(priv, REG_NORMAL_SIE_EP_TX);
	if (val16 & NORMAL_SIE_EP_TX_HIGH_MASK) {
		priv->ep_tx_high_queue = 1;
		priv->ep_tx_count++;
	}

	if (val16 & NORMAL_SIE_EP_TX_NORMAL_MASK) {
		priv->ep_tx_normal_queue = 1;
		priv->ep_tx_count++;
	}

	if (val16 & NORMAL_SIE_EP_TX_LOW_MASK) {
		priv->ep_tx_low_queue = 1;
		priv->ep_tx_count++;
	}


	if (!priv->ep_tx_count) {
		switch (priv->nr_out_eps) {
		case 3:
			priv->ep_tx_low_queue = 1;
			priv->ep_tx_count++;
		case 2:
			priv->ep_tx_normal_queue = 1;
			priv->ep_tx_count++;
		case 1:
			priv->ep_tx_high_queue = 1;
			priv->ep_tx_count++;
			break;
		default:
			dev_info(dev, "Unsupported USB TX end-points\n");
			return -ENOTSUPP;
		}
	}

	return 0;
}
