aac_printf(struct aac_dev *dev, u32 val)
{
	char *cp = dev->printfbuf;
	if (dev->printf_enabled)
	{
		int length = val & 0xffff;
		int level = (val >> 16) & 0xffff;


		if (length > 255)
			length = 255;
		if (cp[length] != 0)
			cp[length] = 0;
		if (level == LOG_AAC_HIGH_ERROR)
			printk(KERN_WARNING "%s:%s", dev->name, cp);
		else
			printk(KERN_INFO "%s:%s", dev->name, cp);
	}
	memset(cp, 0, 256);
}
