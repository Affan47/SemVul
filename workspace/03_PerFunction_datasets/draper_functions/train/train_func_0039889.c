usc_reset( struct mgsl_struct *info )
{
	if ( info->bus_type == MGSL_BUS_TYPE_PCI ) {
		int i;
		u32 readval;


		volatile u32 *MiscCtrl = (u32 *)(info->lcr_base + 0x50);
		u32 *LCR0BRDR = (u32 *)(info->lcr_base + 0x28);

		info->misc_ctrl_value |= BIT30;
		*MiscCtrl = info->misc_ctrl_value;


		for(i=0;i<10;i++)
			readval = *MiscCtrl;

		info->misc_ctrl_value &= ~BIT30;
		*MiscCtrl = info->misc_ctrl_value;

		*LCR0BRDR = BUS_DESCRIPTOR(
			1,
			2,
			2,
			0,
			4,
			0,
			0,
			5
			);
	} else {

		outb( 0,info->io_base + 8 );
	}

	info->mbre_bit = 0;
	info->loopback_bits = 0;
	info->usc_idle_mode = 0;


	outw( 0x000c,info->io_base + SDPIN );


	outw( 0,info->io_base );
	outw( 0,info->io_base + CCAR );


	usc_RTCmd( info, RTCmd_SelectLittleEndian );


	usc_OutReg( info, PCR, 0xf0f5 );


	usc_OutReg( info, IOCR, 0x0004 );

}
