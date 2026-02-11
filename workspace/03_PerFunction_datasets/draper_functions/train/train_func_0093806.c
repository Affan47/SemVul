rtl8192cu_power_on(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;
	u32 val32;
	int i;

	for (i = 100; i; i--) {
		val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO);
		if (val8 & APS_FSMCO_PFM_ALDN)
			break;
	}

	if (!i) {
		pr_info("%s: Poll failed\n", __func__);
		return -ENODEV;
	}


	rtl8xxxu_write8(priv, REG_RSV_CTRL, 0x0);
	rtl8xxxu_write8(priv, REG_SPS0_CTRL, 0x2b);
	udelay(100);

	val8 = rtl8xxxu_read8(priv, REG_LDOV12D_CTRL);
	if (!(val8 & LDOV12D_ENABLE)) {
		pr_info("%s: Enabling LDOV12D (%02x)\n", __func__, val8);
		val8 |= LDOV12D_ENABLE;
		rtl8xxxu_write8(priv, REG_LDOV12D_CTRL, val8);

		udelay(100);

		val8 = rtl8xxxu_read8(priv, REG_SYS_ISO_CTRL);
		val8 &= ~SYS_ISO_MD2PP;
		rtl8xxxu_write8(priv, REG_SYS_ISO_CTRL, val8);
	}


	val16 = rtl8xxxu_read16(priv, REG_APS_FSMCO);
	val16 |= APS_FSMCO_MAC_ENABLE;
	rtl8xxxu_write16(priv, REG_APS_FSMCO, val16);

	for (i = 1000; i; i--) {
		val16 = rtl8xxxu_read16(priv, REG_APS_FSMCO);
		if (!(val16 & APS_FSMCO_MAC_ENABLE))
			break;
	}
	if (!i) {
		pr_info("%s: FSMCO_MAC_ENABLE poll failed\n", __func__);
		return -EBUSY;
	}


	val16 = APS_FSMCO_HW_SUSPEND | APS_FSMCO_ENABLE_POWERDOWN |
		APS_FSMCO_PFM_ALDN;
	rtl8xxxu_write16(priv, REG_APS_FSMCO, val16);


	val16 = rtl8xxxu_read16(priv, REG_SYS_ISO_CTRL);
	val16 &= ~SYS_ISO_DIOR;
	rtl8xxxu_write16(priv, REG_SYS_ISO_CTRL, val16);

	val8 = rtl8xxxu_read8(priv, REG_APSD_CTRL);
	val8 &= ~APSD_CTRL_OFF;
	rtl8xxxu_write8(priv, REG_APSD_CTRL, val8);
	for (i = 200; i; i--) {
		val8 = rtl8xxxu_read8(priv, REG_APSD_CTRL);
		if (!(val8 & APSD_CTRL_OFF_STATUS))
			break;
	}

	if (!i) {
		pr_info("%s: APSD_CTRL poll failed\n", __func__);
		return -EBUSY;
	}


	val16 = rtl8xxxu_read16(priv, REG_CR);
	val16 |= CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE |
		CR_TXDMA_ENABLE | CR_RXDMA_ENABLE | CR_PROTOCOL_ENABLE |
		CR_SCHEDULE_ENABLE | CR_MAC_TX_ENABLE | CR_MAC_RX_ENABLE;
	rtl8xxxu_write16(priv, REG_CR, val16);


	if (priv->rtlchip == 0x8188c && priv->hi_pa) {
		val32 = rtl8xxxu_read32(priv, REG_FPGA0_XCD_RF_PARM);
		val32 &= ~BIT(1);
		rtl8xxxu_write32(priv, REG_FPGA0_XCD_RF_PARM, val32);
	}
	return 0;
}
