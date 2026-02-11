toggle_ecc_err_reporting(struct ecc_settings *s, u16 nid, bool on)
{
	cpumask_var_t cmask;
	int cpu;

	if (!zalloc_cpumask_var(&cmask, GFP_KERNEL)) {
		amd64_warn("%s: error allocating mask\n", __func__);
		return false;
	}

	get_cpus_on_this_dct_cpumask(cmask, nid);

	rdmsr_on_cpus(cmask, MSR_IA32_MCG_CTL, msrs);

	for_each_cpu(cpu, cmask) {

		struct msr *reg = per_cpu_ptr(msrs, cpu);

		if (on) {
			if (reg->l & MSR_MCGCTL_NBE)
				s->flags.nb_mce_enable = 1;

			reg->l |= MSR_MCGCTL_NBE;
		} else {


			if (!s->flags.nb_mce_enable)
				reg->l &= ~MSR_MCGCTL_NBE;
		}
	}
	wrmsr_on_cpus(cmask, MSR_IA32_MCG_CTL, msrs);

	free_cpumask_var(cmask);

	return 0;
}
