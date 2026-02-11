alternatives_enable_smp(void)
{
	struct smp_alt_module *mod;


	BUG_ON(num_possible_cpus() == 1);

	mutex_lock(&smp_alt);

	if (uniproc_patched) {
		pr_info("switching to SMP code\n");
		BUG_ON(num_online_cpus() != 1);
		clear_cpu_cap(&boot_cpu_data, X86_FEATURE_UP);
		clear_cpu_cap(&cpu_data(0), X86_FEATURE_UP);
		list_for_each_entry(mod, &smp_alt_modules, next)
			alternatives_smp_lock(mod->locks, mod->locks_end,
					      mod->text, mod->text_end);
		uniproc_patched = false;
	}
	mutex_unlock(&smp_alt);
}
