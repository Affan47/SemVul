apic_bsp_setup(bool upmode)
{
	int id;

	connect_bsp_APIC();
	if (upmode)
		apic_bsp_up_setup();
	setup_local_APIC();

	if (x2apic_mode)
		id = apic_read(APIC_LDR);
	else
		id = GET_APIC_LOGICAL_ID(apic_read(APIC_LDR));

	enable_IO_APIC();
	end_local_APIC_setup();
	irq_remap_enable_fault_handling();
	setup_IO_APIC();

	x86_init.timers.setup_percpu_clockev();
	return id;
}
