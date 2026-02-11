mp_irqdomain_activate(struct irq_domain *domain,
			   struct irq_data *irq_data)
{
	unsigned long flags;
	struct irq_pin_list *entry;
	struct mp_chip_data *data = irq_data->chip_data;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	for_each_irq_pin(entry, data->irq_2_pin)
		__ioapic_write_entry(entry->apic, entry->pin, data->entry);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
}
