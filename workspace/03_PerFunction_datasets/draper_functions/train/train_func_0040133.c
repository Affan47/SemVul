init_adapter(SLMP_INFO *info)
{
	int i;


	volatile u32 *MiscCtrl = (u32 *)(info->lcr_base + 0x50);
	u32 readval;

	info->misc_ctrl_value |= BIT30;
	*MiscCtrl = info->misc_ctrl_value;


	for(i=0;i<10;i++)
		readval = *MiscCtrl;

	info->misc_ctrl_value &= ~BIT30;
	*MiscCtrl = info->misc_ctrl_value;


	info->ctrlreg_value = 0xaa;
	write_control_reg(info);

	{
		volatile u32 *LCR1BRDR = (u32 *)(info->lcr_base + 0x2c);
		lcr1_brdr_value &= ~(BIT5 + BIT4 + BIT3);

		switch(read_ahead_count)
		{
		case 16:
			lcr1_brdr_value |= BIT5 + BIT4 + BIT3;
			break;
		case 8:
			lcr1_brdr_value |= BIT5 + BIT4;
			break;
		case 4:
			lcr1_brdr_value |= BIT5 + BIT3;
			break;
		case 0:
			lcr1_brdr_value |= BIT5;
			break;
		}

		*LCR1BRDR = lcr1_brdr_value;
		*MiscCtrl = misc_ctrl_value;
	}

	sca_init(info->port_array[0]);
	sca_init(info->port_array[2]);

	return true;
}
