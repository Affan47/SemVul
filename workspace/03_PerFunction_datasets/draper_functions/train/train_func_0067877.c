dsp_get_vers(sb_devc * devc)
{
	int i;

	unsigned long   flags;

	DDB(printk("Entered dsp_get_vers()\n"));
	spin_lock_irqsave(&devc->lock, flags);
	devc->major = devc->minor = 0;
	sb_dsp_command(devc, 0xe1);

	for (i = 100000; i; i--)
	{
		if (inb(DSP_DATA_AVAIL) & 0x80)
		{
			if (devc->major == 0)
				devc->major = inb(DSP_READ);
			else
			{
				devc->minor = inb(DSP_READ);
				break;
			}
		}
	}
	spin_unlock_irqrestore(&devc->lock, flags);
	DDB(printk("DSP version %d.%02d\n", devc->major, devc->minor));
}
