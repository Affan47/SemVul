velocity_set_media_mode(struct velocity_info *vptr,
				   u32 mii_status)
{
	struct mac_regs *regs = vptr->mac_regs;

	vptr->mii_status = mii_check_media_mode(vptr->mac_regs);


	set_mii_flow_control(vptr);

	if (PHYID_GET_PHY_ID(vptr->phy_id) == PHYID_CICADA_CS8201) {
		MII_REG_BITS_ON(AUXCR_MDPPS, MII_REG_AUXCR,
				vptr->mac_regs);
	}


	if (mii_status & VELOCITY_AUTONEG_ENABLE) {
		printf("Velocity is AUTO mode\n");

		BYTE_REG_BITS_OFF(CHIPGCR_FCMODE, &regs->CHIPGCR);

		MII_REG_BITS_ON(ANAR_TXFD | ANAR_TX | ANAR_10FD | ANAR_10,
				MII_REG_ANAR, vptr->mac_regs);
		MII_REG_BITS_ON(G1000CR_1000FD | G1000CR_1000,
				MII_REG_G1000CR, vptr->mac_regs);
		MII_REG_BITS_ON(BMCR_SPEED1G, MII_REG_BMCR,
				vptr->mac_regs);


		mii_set_auto_on(vptr);
	} else {
		u16 ANAR;
		u8 CHIPGCR;


		BYTE_REG_BITS_ON(CHIPGCR_FCMODE, &regs->CHIPGCR);

		CHIPGCR = readb(&regs->CHIPGCR);
		CHIPGCR &= ~CHIPGCR_FCGMII;

		if (mii_status & VELOCITY_DUPLEX_FULL) {
			CHIPGCR |= CHIPGCR_FCFDX;
			writeb(CHIPGCR, &regs->CHIPGCR);
			printf
			    ("DEBUG: set Velocity to forced full mode\n");
			if (vptr->rev_id < REV_ID_VT3216_A0)
				BYTE_REG_BITS_OFF(TCR_TB2BDIS, &regs->TCR);
		} else {
			CHIPGCR &= ~CHIPGCR_FCFDX;
			printf
			    ("DEBUG: set Velocity to forced half mode\n");
			writeb(CHIPGCR, &regs->CHIPGCR);
			if (vptr->rev_id < REV_ID_VT3216_A0)
				BYTE_REG_BITS_ON(TCR_TB2BDIS, &regs->TCR);
		}

		MII_REG_BITS_OFF(G1000CR_1000FD | G1000CR_1000,
				 MII_REG_G1000CR, vptr->mac_regs);

		if (!(mii_status & VELOCITY_DUPLEX_FULL)
		    && (mii_status & VELOCITY_SPEED_10)) {
			BYTE_REG_BITS_OFF(TESTCFG_HBDIS, &regs->TESTCFG);
		} else {
			BYTE_REG_BITS_ON(TESTCFG_HBDIS, &regs->TESTCFG);
		}

		velocity_mii_read(vptr->mac_regs, MII_REG_ANAR, &ANAR);
		ANAR &= (~(ANAR_TXFD | ANAR_TX | ANAR_10FD | ANAR_10));
		if (mii_status & VELOCITY_SPEED_100) {
			if (mii_status & VELOCITY_DUPLEX_FULL)
				ANAR |= ANAR_TXFD;
			else
				ANAR |= ANAR_TX;
		} else {
			if (mii_status & VELOCITY_DUPLEX_FULL)
				ANAR |= ANAR_10FD;
			else
				ANAR |= ANAR_10;
		}
		velocity_mii_write(vptr->mac_regs, MII_REG_ANAR, ANAR);

		mii_set_auto_on(vptr);

	}


	return VELOCITY_LINK_CHANGE;
}
