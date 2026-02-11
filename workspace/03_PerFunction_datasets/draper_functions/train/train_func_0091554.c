TLan_PhyStartLink(struct nic *nic)
{

	u16 ability;
	u16 control;
	u16 data;
	u16 phy;
	u16 status;
	u16 tctl;

	phy = priv->phy[priv->phyNum];
	DBG ( "%s: Trying to activate link.\n", priv->nic_name );
	TLan_MiiReadReg(nic, phy, MII_BMSR, &status);
	TLan_MiiReadReg(nic, phy, MII_BMSR, &ability);

	if ((status & BMSR_ANEGCAPABLE) && (!priv->aui)) {
		ability = status >> 11;
		if (priv->speed == TLAN_SPEED_10 &&
		    priv->duplex == TLAN_DUPLEX_HALF) {
			TLan_MiiWriteReg(nic, phy, MII_BMCR, 0x0000);
		} else if (priv->speed == TLAN_SPEED_10 &&
			   priv->duplex == TLAN_DUPLEX_FULL) {
			priv->tlanFullDuplex = TRUE;
			TLan_MiiWriteReg(nic, phy, MII_BMCR, 0x0100);
		} else if (priv->speed == TLAN_SPEED_100 &&
			   priv->duplex == TLAN_DUPLEX_HALF) {
			TLan_MiiWriteReg(nic, phy, MII_BMCR, 0x2000);
		} else if (priv->speed == TLAN_SPEED_100 &&
			   priv->duplex == TLAN_DUPLEX_FULL) {
			priv->tlanFullDuplex = TRUE;
			TLan_MiiWriteReg(nic, phy, MII_BMCR, 0x2100);
		} else {


			TLan_MiiWriteReg(nic, phy, MII_ADVERTISE,
					 (ability << 5) | 1);

			TLan_MiiWriteReg(nic, phy, MII_BMCR, 0x1000);

			TLan_MiiWriteReg(nic, phy, MII_BMCR, 0x1200);


			DBG ( "TLAN: %s: Starting autonegotiation.\n",
			       priv->nic_name );
			mdelay(4000);
			TLan_PhyFinishAutoNeg(nic);

			return;
		}

	}

	if ((priv->aui) && (priv->phyNum != 0)) {
		priv->phyNum = 0;
		data =
		    TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN |
		    TLAN_NET_CFG_PHY_EN;
		TLan_DioWrite16(BASE, TLAN_NET_CONFIG, data);
		mdelay(50);

		TLan_PhyPowerDown(nic);
		return;
	} else if (priv->phyNum == 0) {
		control = 0;
		TLan_MiiReadReg(nic, phy, TLAN_TLPHY_CTL, &tctl);
		if (priv->aui) {
			tctl |= TLAN_TC_AUISEL;
		} else {
			tctl &= ~TLAN_TC_AUISEL;
			if (priv->duplex == TLAN_DUPLEX_FULL) {
				control |= BMCR_FULLDPLX;
				priv->tlanFullDuplex = TRUE;
			}
			if (priv->speed == TLAN_SPEED_100) {
				control |= BMCR_SPEED100;
			}
		}
		TLan_MiiWriteReg(nic, phy, MII_BMCR, control);
		TLan_MiiWriteReg(nic, phy, TLAN_TLPHY_CTL, tctl);
	}


	mdelay(2000);
	TLan_FinishReset(nic);

}
