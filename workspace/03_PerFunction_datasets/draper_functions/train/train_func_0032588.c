acpi_throttling_rdmsr(u64 *value)
{
	u64 msr_high, msr_low;
	u64 msr = 0;
	int ret = -1;

	if ((this_cpu_read(cpu_info.x86_vendor) != X86_VENDOR_INTEL) ||
		!this_cpu_has(X86_FEATURE_ACPI)) {
		printk(KERN_ERR PREFIX
			"HARDWARE addr space,NOT supported yet\n");
	} else {
		msr_low = 0;
		msr_high = 0;
		rdmsr_safe(MSR_IA32_THERM_CONTROL,
			(u32 *)&msr_low , (u32 *) &msr_high);
		msr = (msr_high << 32) | msr_low;
		*value = (u64) msr;
		ret = 0;
	}
	return ret;
}
