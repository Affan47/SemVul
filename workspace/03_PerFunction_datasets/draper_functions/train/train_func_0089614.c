mem_cgroup_wb_stats(struct bdi_writeback *wb, unsigned long *pfilepages,
			 unsigned long *pheadroom, unsigned long *pdirty,
			 unsigned long *pwriteback)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(wb->memcg_css);
	struct mem_cgroup *parent;

	*pdirty = mem_cgroup_read_stat(memcg, MEM_CGROUP_STAT_DIRTY);


	*pwriteback = mem_cgroup_read_stat(memcg, MEM_CGROUP_STAT_WRITEBACK);
	*pfilepages = mem_cgroup_nr_lru_pages(memcg, (1 << LRU_INACTIVE_FILE) |
						     (1 << LRU_ACTIVE_FILE));
	*pheadroom = PAGE_COUNTER_MAX;

	while ((parent = parent_mem_cgroup(memcg))) {
		unsigned long ceiling = min(memcg->memory.limit, memcg->high);
		unsigned long used = page_counter_read(&memcg->memory);

		*pheadroom = min(*pheadroom, ceiling - min(ceiling, used));
		memcg = parent;
	}
}
