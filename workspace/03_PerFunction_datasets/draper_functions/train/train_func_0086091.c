setup_IO_APIC_irqs(void)
{
	unsigned int ioapic, pin;
	int idx;

	apic_printk(APIC_VERBOSE, KERN_DEBUG "init IO_APIC IRQs\n");

	for_each_ioapic_pin(ioapic, pin) {
		idx = find_irq_entry(ioapic, pin, mp_INT);
		if (idx < 0)
			apic_printk(APIC_VERBOSE,
				    KERN_DEBUG " apic %d pin %d not connected\n",
				    mpc_ioapic_id(ioapic), pin);
		else
			pin_2_irq(idx, ioapic, pin,
				  ioapic ? 0 : IOAPIC_MAP_ALLOC);
	}
}
