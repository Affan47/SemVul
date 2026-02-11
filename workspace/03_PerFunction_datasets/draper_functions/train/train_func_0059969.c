srcu_torture_stats(void)
{
	int cpu;
	int idx = srcu_ctlp->completed & 0x1;

	pr_alert("%s%s per-CPU(idx=%d):",
		 torture_type, TORTURE_FLAG, idx);
	for_each_possible_cpu(cpu) {
		long c0, c1;

		c0 = (long)per_cpu_ptr(srcu_ctlp->per_cpu_ref, cpu)->c[!idx];
		c1 = (long)per_cpu_ptr(srcu_ctlp->per_cpu_ref, cpu)->c[idx];
		pr_cont(" %d(%ld,%ld)", cpu, c0, c1);
	}
	pr_cont("\n");
}
