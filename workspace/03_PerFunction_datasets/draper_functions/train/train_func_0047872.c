smsc911x_phy_update_flowcontrol(struct smsc911x_data *pdata)
{
	struct phy_device *phy_dev = pdata->phy_dev;
	u32 afc = smsc911x_reg_read(pdata, AFC_CFG);
	u32 flow;
	unsigned long flags;

	if (phy_dev->duplex == DUPLEX_FULL) {
		u16 lcladv = phy_read(phy_dev, MII_ADVERTISE);
		u16 rmtadv = phy_read(phy_dev, MII_LPA);
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		if (cap & FLOW_CTRL_RX)
			flow = 0xFFFF0002;
		else
			flow = 0;

		if (cap & FLOW_CTRL_TX)
			afc |= 0xF;
		else
			afc &= ~0xF;

		SMSC_TRACE(pdata, hw, "rx pause %s, tx pause %s",
			   (cap & FLOW_CTRL_RX ? "enabled" : "disabled"),
			   (cap & FLOW_CTRL_TX ? "enabled" : "disabled"));
	} else {
		SMSC_TRACE(pdata, hw, "half duplex");
		flow = 0;
		afc |= 0xF;
	}

	spin_lock_irqsave(&pdata->mac_lock, flags);
	smsc911x_mac_write(pdata, FLOW, flow);
	spin_unlock_irqrestore(&pdata->mac_lock, flags);

	smsc911x_reg_write(pdata, AFC_CFG, afc);
}
