dm_stat_free(struct rcu_head *head)
{
	int cpu;
	struct dm_stat *s = container_of(head, struct dm_stat, rcu_head);

	kfree(s->histogram_boundaries);
	kfree(s->program_id);
	kfree(s->aux_data);
	for_each_possible_cpu(cpu) {
		dm_kvfree(s->stat_percpu[cpu][0].histogram, s->histogram_alloc_size);
		dm_kvfree(s->stat_percpu[cpu], s->percpu_alloc_size);
	}
	dm_kvfree(s->stat_shared[0].tmp.histogram, s->histogram_alloc_size);
	dm_kvfree(s, s->shared_alloc_size);
}
