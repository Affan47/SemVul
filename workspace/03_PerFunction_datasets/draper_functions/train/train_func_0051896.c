store_select_amcb2_transmit_clock(struct device *d,
		struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long flags;
	unsigned long tmp;
	unsigned char val;

	sscanf(buf, "%lX", &tmp);
	dev_dbg(d, "tmp = 0x%lX\n", tmp);

	val = (unsigned char)tmp;
	spin_lock_irqsave(&event_lock, flags);
		if ((val == CLK_8kHz) || (val == CLK_16_384MHz)) {
			SET_PORT_BITS(TLCLK_REG3, 0xc7, 0x28);
			SET_PORT_BITS(TLCLK_REG1, 0xfb, ~val);
		} else if (val >= CLK_8_592MHz) {
			SET_PORT_BITS(TLCLK_REG3, 0xc7, 0x38);
			switch (val) {
			case CLK_8_592MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 2);
				break;
			case CLK_11_184MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 0);
				break;
			case CLK_34_368MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 3);
				break;
			case CLK_44_736MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 1);
				break;
			}
		} else
			SET_PORT_BITS(TLCLK_REG3, 0xc7, val << 3);

	spin_unlock_irqrestore(&event_lock, flags);

	return strnlen(buf, count);
}
