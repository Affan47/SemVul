mii_init(struct velocity_info *vptr, u32 mii_status)
{
	u16 BMCR;

	switch (PHYID_GET_PHY_ID(vptr->phy_id)) {
	case PHYID_ICPLUS_IP101A:
		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP),
						MII_ADVERTISE, vptr->mac_regs);
		if (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION,
								vptr->mac_regs);
		else
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION,
								vptr->mac_regs);
		MII_REG_BITS_ON(PLED_LALBE, MII_TPISTATUS, vptr->mac_regs);
		break;
	case PHYID_CICADA_CS8201:


		MII_REG_BITS_OFF((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);


		if (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		else
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);


		MII_REG_BITS_ON(PLED_LALBE, MII_TPISTATUS, vptr->mac_regs);
		break;
	case PHYID_VT3216_32BIT:
	case PHYID_VT3216_64BIT:


		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);


		if (vptr->mii_status & VELOCITY_DUPLEX_FULL)
			MII_REG_BITS_ON(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		else
			MII_REG_BITS_OFF(TCSR_ECHODIS, MII_SREVISION, vptr->mac_regs);
		break;

	case PHYID_MARVELL_1000:
	case PHYID_MARVELL_1000S:


		MII_REG_BITS_ON(PSCR_ACRSTX, MII_REG_PSCR, vptr->mac_regs);


		MII_REG_BITS_ON((ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP), MII_ADVERTISE, vptr->mac_regs);
		break;
	default:
		;
	}
	velocity_mii_read(vptr->mac_regs, MII_BMCR, &BMCR);
	if (BMCR & BMCR_ISOLATE) {
		BMCR &= ~BMCR_ISOLATE;
		velocity_mii_write(vptr->mac_regs, MII_BMCR, BMCR);
	}
}
