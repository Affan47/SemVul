print_nego(const unsigned char *msg, int per, int off, int width)
{
	if (per) {
		char buf[20];
		period_to_str(buf, msg[per]);
		printk("period = %s ns ", buf);
	}

	if (off)
		printk("offset = %d ", msg[off]);
	if (width)
		printk("width = %d ", 8 << msg[width]);
}
