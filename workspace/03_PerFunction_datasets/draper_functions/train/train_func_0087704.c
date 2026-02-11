dmfe_set_phyxcer(struct nic *nic __unused)
{
	u16 phy_reg;


	db->cr6_data &= ~0x40000;
	update_cr6(db->cr6_data, BASE);


	if (db->chip_id == PCI_DM9009_ID) {
		phy_reg =
		    phy_read(BASE, db->phy_addr, 18,
			     db->chip_id) & ~0x1000;
		phy_write(BASE, db->phy_addr, 18, phy_reg, db->chip_id);
	}


	phy_reg = phy_read(BASE, db->phy_addr, 4, db->chip_id) & ~0x01e0;

	if (db->media_mode & DMFE_AUTO) {

		phy_reg |= db->PHY_reg4;
	} else {

		switch (db->media_mode) {
		case DMFE_10MHF:
			phy_reg |= 0x20;
			break;
		case DMFE_10MFD:
			phy_reg |= 0x40;
			break;
		case DMFE_100MHF:
			phy_reg |= 0x80;
			break;
		case DMFE_100MFD:
			phy_reg |= 0x100;
			break;
		}
		if (db->chip_id == PCI_DM9009_ID)
			phy_reg &= 0x61;
	}


	if (!(phy_reg & 0x01e0)) {
		phy_reg |= db->PHY_reg4;
		db->media_mode |= DMFE_AUTO;
	}
	phy_write(BASE, db->phy_addr, 4, phy_reg, db->chip_id);


	if (db->chip_type && (db->chip_id == PCI_DM9102_ID))
		phy_write(BASE, db->phy_addr, 0, 0x1800, db->chip_id);
	if (!db->chip_type)
		phy_write(BASE, db->phy_addr, 0, 0x1200, db->chip_id);
}
