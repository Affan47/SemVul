__dm_stat_init_temporary_percpu_totals(struct dm_stat_shared *shared,
						   struct dm_stat *s, size_t x)
{
	int cpu;
	struct dm_stat_percpu *p;

	local_irq_disable();
	p = &s->stat_percpu[smp_processor_id()][x];
	dm_stat_round(s, shared, p);
	local_irq_enable();

	shared->tmp.sectors[READ] = 0;
	shared->tmp.sectors[WRITE] = 0;
	shared->tmp.ios[READ] = 0;
	shared->tmp.ios[WRITE] = 0;
	shared->tmp.merges[READ] = 0;
	shared->tmp.merges[WRITE] = 0;
	shared->tmp.ticks[READ] = 0;
	shared->tmp.ticks[WRITE] = 0;
	shared->tmp.io_ticks[READ] = 0;
	shared->tmp.io_ticks[WRITE] = 0;
	shared->tmp.io_ticks_total = 0;
	shared->tmp.time_in_queue = 0;

	if (s->n_histogram_entries)
		memset(shared->tmp.histogram, 0, (s->n_histogram_entries + 1) * sizeof(unsigned long long));

	for_each_possible_cpu(cpu) {
		p = &s->stat_percpu[cpu][x];
		shared->tmp.sectors[READ] += ACCESS_ONCE(p->sectors[READ]);
		shared->tmp.sectors[WRITE] += ACCESS_ONCE(p->sectors[WRITE]);
		shared->tmp.ios[READ] += ACCESS_ONCE(p->ios[READ]);
		shared->tmp.ios[WRITE] += ACCESS_ONCE(p->ios[WRITE]);
		shared->tmp.merges[READ] += ACCESS_ONCE(p->merges[READ]);
		shared->tmp.merges[WRITE] += ACCESS_ONCE(p->merges[WRITE]);
		shared->tmp.ticks[READ] += ACCESS_ONCE(p->ticks[READ]);
		shared->tmp.ticks[WRITE] += ACCESS_ONCE(p->ticks[WRITE]);
		shared->tmp.io_ticks[READ] += ACCESS_ONCE(p->io_ticks[READ]);
		shared->tmp.io_ticks[WRITE] += ACCESS_ONCE(p->io_ticks[WRITE]);
		shared->tmp.io_ticks_total += ACCESS_ONCE(p->io_ticks_total);
		shared->tmp.time_in_queue += ACCESS_ONCE(p->time_in_queue);
		if (s->n_histogram_entries) {
			unsigned i;
			for (i = 0; i < s->n_histogram_entries + 1; i++)
				shared->tmp.histogram[i] += ACCESS_ONCE(p->histogram[i]);
		}
	}
}
