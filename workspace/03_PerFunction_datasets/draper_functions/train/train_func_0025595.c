snbep_uncore_cpu_init(void)
{
	if (snbep_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		snbep_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = snbep_msr_uncores;
}
