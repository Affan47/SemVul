isr_rxrdy(SLMP_INFO * info)
{
	u16 status;
	unsigned char DataByte;
 	struct	mgsl_icount *icount = &info->icount;

	if ( debug_level >= DEBUG_LEVEL_ISR )
		printk("%s(%d):%s isr_rxrdy\n",
			__FILE__,__LINE__,info->device_name);

	while((status = read_reg(info,CST0)) & BIT0)
	{
		int flag = 0;
		bool over = false;
		DataByte = read_reg(info,TRB);

		icount->rx++;

		if ( status & (PE + FRME + OVRN) ) {
			printk("%s(%d):%s rxerr=%04X\n",
				__FILE__,__LINE__,info->device_name,status);


			if (status & PE)
				icount->parity++;
			else if (status & FRME)
				icount->frame++;
			else if (status & OVRN)
				icount->overrun++;


			if (status & info->ignore_status_mask2)
				continue;

			status &= info->read_status_mask2;

			if (status & PE)
				flag = TTY_PARITY;
			else if (status & FRME)
				flag = TTY_FRAME;
			if (status & OVRN) {


				over = true;
			}
		}

		tty_insert_flip_char(&info->port, DataByte, flag);
		if (over)
			tty_insert_flip_char(&info->port, 0, TTY_OVERRUN);
	}

	if ( debug_level >= DEBUG_LEVEL_ISR ) {
		printk("%s(%d):%s rx=%d brk=%d parity=%d frame=%d overrun=%d\n",
			__FILE__,__LINE__,info->device_name,
			icount->rx,icount->brk,icount->parity,
			icount->frame,icount->overrun);
	}

	tty_flip_buffer_push(&info->port);
}
