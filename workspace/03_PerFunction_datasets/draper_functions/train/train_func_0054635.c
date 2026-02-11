fixup_ht_bug(void)
{
	int cpu = smp_processor_id();
	int w, c;


	if (!(x86_pmu.flags & PMU_FL_EXCL_ENABLED))
		return 0;

	w = cpumask_weight(topology_sibling_cpumask(cpu));
	if (w > 1) {
		pr_info("PMU erratum BJ122, BV98, HSD29 worked around, HT is on\n");
		return 0;
	}

	if (lockup_detector_suspend() != 0) {
		pr_debug("failed to disable PMU erratum BJ122, BV98, HSD29 workaround\n");
		return 0;
	}

	x86_pmu.flags &= ~(PMU_FL_EXCL_CNTRS | PMU_FL_EXCL_ENABLED);

	x86_pmu.start_scheduling = NULL;
	x86_pmu.commit_scheduling = NULL;
	x86_pmu.stop_scheduling = NULL;

	lockup_detector_resume();

	get_online_cpus();

	for_each_online_cpu(c) {
		free_excl_cntrs(c);
	}

	put_online_cpus();
	pr_info("PMU erratum BJ122, BV98, HSD29 workaround disabled, HT off\n");
	return 0;
}
