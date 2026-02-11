print_ICs(void)
{
	if (apic_verbosity == APIC_QUIET)
		return 0;

	print_PIC();


	if (!cpu_has_apic && !apic_from_smp_config())
		return 0;

	print_local_APICs(show_lapic);
	print_IO_APICs();

	return 0;
}
