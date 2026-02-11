find_isa_irq_pin(int irq, int type)
{
	int i;

	for (i = 0; i < mp_irq_entries; i++) {
		int lbus = mp_irqs[i].srcbus;

		if (test_bit(lbus, mp_bus_not_pci) &&
		    (mp_irqs[i].irqtype == type) &&
		    (mp_irqs[i].srcbusirq == irq))

			return mp_irqs[i].dstirq;
	}
	return -1;
}
