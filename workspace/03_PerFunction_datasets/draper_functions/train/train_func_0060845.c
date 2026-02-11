mp_alloc_timer_irq(int ioapic, int pin)
{
	int irq = -1;
	struct irq_domain *domain = mp_ioapic_irqdomain(ioapic);

	if (domain) {
		struct irq_alloc_info info;

		ioapic_set_alloc_attr(&info, NUMA_NO_NODE, 0, 0);
		info.ioapic_id = mpc_ioapic_id(ioapic);
		info.ioapic_pin = pin;
		mutex_lock(&ioapic_mutex);
		irq = alloc_isa_irq_from_domain(domain, 0, ioapic, pin, &info);
		mutex_unlock(&ioapic_mutex);
	}

	return irq;
}
