release_bts_buffer(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	if (!ds || !x86_pmu.bts)
		return;

	dsfree((void *)(unsigned long)ds->bts_buffer_base, BTS_BUFFER_SIZE);
	ds->bts_buffer_base = 0;
}
