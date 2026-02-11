fdisk_table_get_partition(
			struct fdisk_table *tb,
			size_t n)
{
	struct fdisk_partition *pa = NULL;
	struct fdisk_iter itr;

	if (!tb)
		return NULL;

	fdisk_reset_iter(&itr, FDISK_ITER_FORWARD);

	while (fdisk_table_next_partition(tb, &itr, &pa) == 0) {
		if (n == 0)
			return pa;
		n--;
	}

	return NULL;
}
