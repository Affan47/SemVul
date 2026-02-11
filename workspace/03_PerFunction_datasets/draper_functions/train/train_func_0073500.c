alloc_ioapic_saved_registers(int idx)
{
	size_t size;

	if (ioapics[idx].saved_registers)
		return;

	size = sizeof(struct IO_APIC_route_entry) * ioapics[idx].nr_registers;
	ioapics[idx].saved_registers = kzalloc(size, GFP_KERNEL);
	if (!ioapics[idx].saved_registers)
		pr_err("IOAPIC %d: suspend/resume impossible!\n", idx);
}
