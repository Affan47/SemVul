ioapic_mask_entry(int apic, int pin)
{
	unsigned long flags;
	union entry_union eu = { .entry.mask = IOAPIC_MASKED };

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	io_apic_write(apic, 0x10 + 2*pin, eu.w1);
	io_apic_write(apic, 0x11 + 2*pin, eu.w2);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
}
