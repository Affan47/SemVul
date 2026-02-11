k8_check_syscfg_dram_mod_en(void)
{
	u32 lo, hi;

	if (!((boot_cpu_data.x86_vendor == X86_VENDOR_AMD) &&
	      (boot_cpu_data.x86 >= 0x0f)))
		return;

	rdmsr(MSR_K8_SYSCFG, lo, hi);
	if (lo & K8_MTRRFIXRANGE_DRAM_MODIFY) {
		printk(KERN_ERR FW_WARN "MTRR: CPU %u: SYSCFG[MtrrFixDramModEn]"
		       " not cleared by BIOS, clearing this bit\n",
		       smp_processor_id());
		lo &= ~K8_MTRRFIXRANGE_DRAM_MODIFY;
		mtrr_wrmsr(MSR_K8_SYSCFG, lo, hi);
	}
}
