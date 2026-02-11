store_enable_clkb1_output(struct device *d,
		 struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long flags;
	unsigned long tmp;
	unsigned char val;

	sscanf(buf, "%lX", &tmp);
	dev_dbg(d, "tmp = 0x%lX\n", tmp);

	val = (unsigned char)tmp;
	spin_lock_irqsave(&event_lock, flags);
	SET_PORT_BITS(TLCLK_REG2, 0xf7, val << 3);
	spin_unlock_irqrestore(&event_lock, flags);

	return strnlen(buf, count);
}
