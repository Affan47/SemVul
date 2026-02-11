shrink_dcache_sb(struct super_block *sb)
{
	long freed;

	do {
		LIST_HEAD(dispose);

		freed = list_lru_walk(&sb->s_dentry_lru,
			dentry_lru_isolate_shrink, &dispose, 1024);

		this_cpu_sub(nr_dentry_unused, freed);
		shrink_dentry_list(&dispose);
		cond_resched();
	} while (list_lru_count(&sb->s_dentry_lru) > 0);
}
