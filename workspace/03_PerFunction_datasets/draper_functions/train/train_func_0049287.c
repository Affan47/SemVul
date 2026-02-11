io_apic_get_redir_entries(int ioapic)
{
	union IO_APIC_reg_01	reg_01;
	unsigned long flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_01.raw = io_apic_read(ioapic, 1);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);


	return reg_01.bits.entries + 1;
}
