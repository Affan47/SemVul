ext4_mb_cleanup_pa(struct ext4_group_info *grp)
{
	struct ext4_prealloc_space *pa;
	struct list_head *cur, *tmp;
	int count = 0;

	list_for_each_safe(cur, tmp, &grp->bb_prealloc_list) {
		pa = list_entry(cur, struct ext4_prealloc_space, pa_group_list);
		list_del(&pa->pa_group_list);
		count++;
		kmem_cache_free(ext4_pspace_cachep, pa);
	}
	if (count)
		mb_debug(1, "mballoc: %u PAs left\n", count);

}
