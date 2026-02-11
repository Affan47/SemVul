APIC_init_uniprocessor(void)
{
	if (disable_apic) {
		pr_info("Apic disabled\n");
		return -1;
	}
#ifdef CONFIG_X86_64
	if (!cpu_has_apic) {
		disable_apic = 1;
		pr_info("Apic disabled by BIOS\n");
		return -1;
	}
#else
	if (!smp_found_config && !cpu_has_apic)
		return -1;


	if (!cpu_has_apic &&
	    APIC_INTEGRATED(apic_version[boot_cpu_physical_apicid])) {
		pr_err("BIOS bug, local APIC 0x%x not detected!...\n",
			boot_cpu_physical_apicid);
		return -1;
	}
#endif

	if (!smp_found_config)
		disable_ioapic_support();

	default_setup_apic_routing();
	apic_bsp_setup(true);
	return 0;
}
