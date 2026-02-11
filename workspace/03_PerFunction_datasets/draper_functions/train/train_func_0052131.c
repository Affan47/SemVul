init_IO_APIC_traps(void)
{
	struct irq_cfg *cfg;
	unsigned int irq;

	for_each_active_irq(irq) {
		cfg = irq_cfg(irq);
		if (IO_APIC_IRQ(irq) && cfg && !cfg->vector) {


			if (irq < nr_legacy_irqs())
				legacy_pic->make_irq(irq);
			else

				irq_set_chip(irq, &no_irq_chip);
		}
	}
}
