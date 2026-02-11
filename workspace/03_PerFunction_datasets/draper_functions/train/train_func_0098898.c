isr_txdmaok(SLMP_INFO * info)
{
	unsigned char status_reg1 = read_reg(info, SR1);

	write_reg(info, TXDMA + DIR, 0x00);
	write_reg(info, TXDMA + DSR, 0xc0);
	write_reg(info, TXDMA + DCMD, SWABORT);

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_txdmaok(), status=%02x\n",
			__FILE__,__LINE__,info->device_name,status_reg1);


	write_reg16(info, TRC0, 0);
	info->ie0_value |= TXRDYE;
	write_reg(info, IE0, info->ie0_value);
}
