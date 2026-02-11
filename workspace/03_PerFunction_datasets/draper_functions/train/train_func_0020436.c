pcips2_interrupt(int irq, void *devid)
{
	struct pcips2_data *ps2if = devid;
	unsigned char status, scancode;
	int handled = 0;

	do {
		unsigned int flag;

		status = inb(ps2if->base + PS2_STATUS);
		if (!(status & PS2_STAT_RXFULL))
			break;
		handled = 1;
		scancode = inb(ps2if->base + PS2_DATA);
		if (status == 0xff && scancode == 0xff)
			break;

		flag = (status & PS2_STAT_PARITY) ? 0 : SERIO_PARITY;

		if (hweight8(scancode) & 1)
			flag ^= SERIO_PARITY;

		serio_interrupt(ps2if->io, scancode, flag);
	} while (1);
	return IRQ_RETVAL(handled);
}
