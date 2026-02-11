fdisk_table_sort_partitions(struct fdisk_table *tb,
			int (*cmp)(struct fdisk_partition *,
				   struct fdisk_partition *))
{
	if (!tb)
		return -EINVAL;

	DBG(TAB, ul_debugobj(tb, "Before sort:"));
	ON_DBG(TAB, debug_print_table(tb));

	list_sort(&tb->parts, cmp_parts_wrapper, (void *) cmp);

	DBG(TAB, ul_debugobj(tb, "After sort:"));
	ON_DBG(TAB, debug_print_table(tb));

	return 0;
}
