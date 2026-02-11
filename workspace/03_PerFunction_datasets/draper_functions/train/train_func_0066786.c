status_timeout(unsigned long context)
{
	u16 status = 0;
	SLMP_INFO *info = (SLMP_INFO*)context;
	unsigned long flags;
	unsigned char delta;


	spin_lock_irqsave(&info->lock,flags);
	get_signals(info);
	spin_unlock_irqrestore(&info->lock,flags);


	delta = info->old_signals ^ info->serial_signals;
	info->old_signals = info->serial_signals;

	if (delta & SerialSignal_DSR)
		status |= MISCSTATUS_DSR_LATCHED|(info->serial_signals&SerialSignal_DSR);

	if (delta & SerialSignal_RI)
		status |= MISCSTATUS_RI_LATCHED|(info->serial_signals&SerialSignal_RI);

	if (delta & SerialSignal_DCD)
		status |= MISCSTATUS_DCD_LATCHED|(info->serial_signals&SerialSignal_DCD);

	if (delta & SerialSignal_CTS)
		status |= MISCSTATUS_CTS_LATCHED|(info->serial_signals&SerialSignal_CTS);

	if (status)
		isr_io_pin(info,status);

	mod_timer(&info->status_timer, jiffies + msecs_to_jiffies(10));
}
