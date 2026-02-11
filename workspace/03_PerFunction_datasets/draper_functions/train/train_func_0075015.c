print_PIC(void)
{
	unsigned int v;
	unsigned long flags;

	if (!nr_legacy_irqs())
		return;

	pr_debug("\nprinting PIC contents\n");

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	v = inb(0xa1) << 8 | inb(0x21);
	pr_debug("... PIC  IMR: %04x\n", v);

	v = inb(0xa0) << 8 | inb(0x20);
	pr_debug("... PIC  IRR: %04x\n", v);

	outb(0x0b, 0xa0);
	outb(0x0b, 0x20);
	v = inb(0xa0) << 8 | inb(0x20);
	outb(0x0a, 0xa0);
	outb(0x0a, 0x20);

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);

	pr_debug("... PIC  ISR: %04x\n", v);

	v = inb(0x4d1) << 8 | inb(0x4d0);
	pr_debug("... PIC ELCR: %04x\n", v);
}
