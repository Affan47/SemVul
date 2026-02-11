sync_Arb_IDs(void)
{


	if (modern_apic() || boot_cpu_data.x86_vendor == X86_VENDOR_AMD)
		return;


	apic_wait_icr_idle();

	apic_printk(APIC_DEBUG, "Synchronizing Arb IDs.\n");
	apic_write(APIC_ICR, APIC_DEST_ALLINC |
			APIC_INT_LEVELTRIG | APIC_DM_INIT);
}
