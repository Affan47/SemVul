w83977af_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct w83977af_ir *self;
	__u8 set, icr, isr;
	int iobase;

	self = netdev_priv(dev);

	iobase = self->io.fir_base;


	set = inb(iobase+SSR);
	switch_bank(iobase, SET0);

	icr = inb(iobase+ICR);
	isr = inb(iobase+ISR) & icr;

	outb(0, iobase+ICR);

	if (isr) {

		if (self->io.speed > PIO_MAX_SPEED )
			icr = w83977af_fir_interrupt(self, isr);
		else
			icr = w83977af_sir_interrupt(self, isr);
	}

	outb(icr, iobase+ICR);
	outb(set, iobase+SSR);
	return IRQ_RETVAL(isr);
}
