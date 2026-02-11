irq_remapping_disable_io_apic(void)
{


	if (cpu_has_apic || apic_from_smp_config())
		disconnect_bsp_APIC(0);
}
