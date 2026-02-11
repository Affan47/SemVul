dump_hrtimer_data(void)
{
	int i, j;
	int hrtimer_max_clock_bases, max_hrtimer_bases;
	struct syment * hrtimer_bases;

	hrtimer_max_clock_bases = 0;
	max_hrtimer_bases = 0;


	if (VALID_STRUCT(hrtimer_clock_base)) {
		hrtimer_max_clock_bases = 2;
		if (symbol_exists("ktime_get_boottime"))
			hrtimer_max_clock_bases = 3;
	} else if (VALID_STRUCT(hrtimer_base)) {
		max_hrtimer_bases = 2;
	} else
		option_not_supported('r');

	hrtimer_bases = per_cpu_symbol_search("hrtimer_bases");
	for (i = 0; i < kt->cpus; i++) {
		if (i)
			fprintf(fp, "\n");
		fprintf(fp, "CPU: %d  ", i);
		if (VALID_STRUCT(hrtimer_clock_base)) {
			fprintf(fp, "HRTIMER_CPU_BASE: %lx\n",
				(ulong)(hrtimer_bases->value +
				kt->__per_cpu_offset[i]));

			for (j = 0; j < hrtimer_max_clock_bases; j++) {
				if (j)
					fprintf(fp, "\n");
				dump_hrtimer_clock_base(
					(void *)(hrtimer_bases->value) +
					kt->__per_cpu_offset[i], j);
			}
		} else {
			fprintf(fp, "\n");
			for (j = 0; j < max_hrtimer_bases; j++) {
				if (j)
					fprintf(fp, "\n");
				dump_hrtimer_base(
					(void *)(hrtimer_bases->value) +
					kt->__per_cpu_offset[i], j);
			}
		}
	}
}
