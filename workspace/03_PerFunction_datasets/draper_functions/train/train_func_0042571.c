dmfe_process_mode(struct dmfe_board_info *db)
{
	u16 phy_reg;


	if (db->op_mode & 0x4)
		db->cr6_data |= CR6_FDM;
	else
		db->cr6_data &= ~CR6_FDM;


	if (db->op_mode & 0x10)
		db->cr6_data |= 0x40000;
	else
		db->cr6_data &= ~0x40000;

	update_cr6(db->cr6_data, db->ioaddr);


	if ( !(db->media_mode & 0x18)) {

		phy_reg = dmfe_phy_read(db->ioaddr, db->phy_addr, 6, db->chip_id);
		if ( !(phy_reg & 0x1) ) {

			phy_reg = 0x0;
			switch(db->op_mode) {
			case DMFE_10MHF: phy_reg = 0x0; break;
			case DMFE_10MFD: phy_reg = 0x100; break;
			case DMFE_100MHF: phy_reg = 0x2000; break;
			case DMFE_100MFD: phy_reg = 0x2100; break;
			}
			dmfe_phy_write(db->ioaddr,
				       db->phy_addr, 0, phy_reg, db->chip_id);
       			if ( db->chip_type && (db->chip_id == PCI_DM9102_ID) )
				mdelay(20);
			dmfe_phy_write(db->ioaddr,
				       db->phy_addr, 0, phy_reg, db->chip_id);
		}
	}
}
