chip_intel_82093AA_n_reset_set(void *_css, unsigned int n_val)
{
	struct cpssp *css = (struct cpssp *) _css;
	unsigned int irq;

	css->id = 8;
	css->arbitration = 0x0;
	for (irq = 0; irq < 24; irq++) {
		css->ioredtbl[irq].destination = 0x00;
		css->ioredtbl[irq].mask = 1;
		css->ioredtbl[irq].trigger_mode = 0;
		css->ioredtbl[irq].remote_irr = 0;
		css->ioredtbl[irq].polarity = 0;
		css->ioredtbl[irq].delivery_status = 0;
		css->ioredtbl[irq].destination_mode = 0;
		css->ioredtbl[irq].delivery_mode = 0x0;
		css->ioredtbl[irq].vector = 0x00;
	}
}
