mdio_clause45_check_mmds ( struct efab_nic *efab )
{
	int mmd = 0;
	int devices = falcon_mdio_read ( efab, MDIO_MMD_PHYXS,
					 MDIO_MMDREG_DEVS0 );
	int mmd_mask = efab->phy_op->mmds;


	if ( devices < 0 ) {
		EFAB_ERR ( "Failed to read devices present\n" );
		return -EIO;
	}
	if ( ( devices & mmd_mask ) != mmd_mask ) {
		EFAB_ERR ( "required MMDs not present: got %x, wanted %x\n",
			   devices, mmd_mask );
		return -EIO;
	}


	while ( mmd_mask ) {
		if ( mmd_mask & 1 ) {
			efab_dword_t reg;
			int status;
			reg.opaque = falcon_mdio_read ( efab, mmd,
							MDIO_MMDREG_STAT2 );
			status = EFAB_DWORD_FIELD ( reg,
						    MDIO_MMDREG_STAT2_PRESENT );
			if ( status != MDIO_MMDREG_STAT2_PRESENT_VAL ) {


				return -EIO;
			}
		}
		mmd_mask >>= 1;
		mmd++;
	}

	return 0;
}
