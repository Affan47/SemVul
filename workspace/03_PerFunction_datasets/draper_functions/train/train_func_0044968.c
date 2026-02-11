intel_init_cmci(void)
{
	int banks;

	if (!cmci_supported(&banks))
		return;

	mce_threshold_vector = intel_threshold_interrupt;
	cmci_discover(banks);


	apic_write(APIC_LVTCMCI, THRESHOLD_APIC_VECTOR|APIC_DM_FIXED);
	cmci_recheck();
}
