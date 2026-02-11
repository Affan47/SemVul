ioapic_write_entry(int apic, int pin, struct IO_APIC_route_entry e)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	__ioapic_write_entry(apic, pin, e);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
}
