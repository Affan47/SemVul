velocity_set_media_mode(struct velocity_info *vptr, u32 mii_status)
{
	u32 curr_status;
	struct mac_regs __iomem *regs = vptr->mac_regs;

	vptr->mii_status = mii_check_media_mode(vptr->mac_regs);
	curr_status = vptr->mii_status & (~VELOCITY_LINK_FAIL);


	set_mii_flow_control(vptr);


	if (PHYID_GET_PHY_ID(vptr->phy_id) == PHYID_CICADA_CS8201)
		MII_REG_BITS_ON(AUXCR_MDPPS, MII_NCONFIG, vptr->mac_regs);


	if (mii_status & VELOCITY_AUTONEG_ENABLE) {
		VELOCITY_PRT(MSG_LEVEL_INFO, "Velocity is AUTO mode\n");

		BYTE_REG_BITS_OFF(CHIPGCR_FCMODE, &regs->CHIPGCR);

		MII_REG_BITS_ON(ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF, MII_ADVERTISE, vptr->mac_regs);
		MII_REG_BITS_ON(ADVERTISE_1000FULL | ADVERTISE_1000HALF, MII_CTRL1000, vptr->mac_regs);
		MII_REG_BITS_ON(BMCR_SPEED1000, MII_BMCR, vptr->mac_regs);


		mii_set_auto_on(vptr);
	} else {
		u16 CTRL1000;
		u16 ANAR;
		u8 CHIPGCR;


		BYTE_REG_BITS_ON(CHIPGCR_FCMODE, &regs->CHIPGCR);

		CHIPGCR = readb(&regs->CHIPGCR);

		if (mii_status & VELOCITY_SPEED_1000)
			CHIPGCR |= CHIPGCR_FCGMII;
		else
			CHIPGCR &= ~CHIPGCR_FCGMII;

		if (mii_status & VELOCITY_DUPLEX_FULL) {
			CHIPGCR |= CHIPGCR_FCFDX;
			writeb(CHIPGCR, &regs->CHIPGCR);
			VELOCITY_PRT(MSG_LEVEL_INFO, "set Velocity to forced full mode\n");
			if (vptr->rev_id < REV_ID_VT3216_A0)
				BYTE_REG_BITS_OFF(TCR_TB2BDIS, &regs->TCR);
		} else {
			CHIPGCR &= ~CHIPGCR_FCFDX;
			VELOCITY_PRT(MSG_LEVEL_INFO, "set Velocity to forced half mode\n");
			writeb(CHIPGCR, &regs->CHIPGCR);
			if (vptr->rev_id < REV_ID_VT3216_A0)
				BYTE_REG_BITS_ON(TCR_TB2BDIS, &regs->TCR);
		}

		velocity_mii_read(vptr->mac_regs, MII_CTRL1000, &CTRL1000);
		CTRL1000 &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);
		if ((mii_status & VELOCITY_SPEED_1000) &&
		    (mii_status & VELOCITY_DUPLEX_FULL)) {
			CTRL1000 |= ADVERTISE_1000FULL;
		}
		velocity_mii_write(vptr->mac_regs, MII_CTRL1000, CTRL1000);

		if (!(mii_status & VELOCITY_DUPLEX_FULL) && (mii_status & VELOCITY_SPEED_10))
			BYTE_REG_BITS_OFF(TESTCFG_HBDIS, &regs->TESTCFG);
		else
			BYTE_REG_BITS_ON(TESTCFG_HBDIS, &regs->TESTCFG);


		velocity_mii_read(vptr->mac_regs, MII_ADVERTISE, &ANAR);
		ANAR &= (~(ADVERTISE_100FULL | ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF));
		if (mii_status & VELOCITY_SPEED_100) {
			if (mii_status & VELOCITY_DUPLEX_FULL)
				ANAR |= ADVERTISE_100FULL;
			else
				ANAR |= ADVERTISE_100HALF;
		} else if (mii_status & VELOCITY_SPEED_10) {
			if (mii_status & VELOCITY_DUPLEX_FULL)
				ANAR |= ADVERTISE_10FULL;
			else
				ANAR |= ADVERTISE_10HALF;
		}
		velocity_mii_write(vptr->mac_regs, MII_ADVERTISE, ANAR);

		mii_set_auto_on(vptr);

	}


	return VELOCITY_LINK_CHANGE;
}
