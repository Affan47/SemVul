fdisk_get_partitions(struct fdisk_context *cxt, struct fdisk_table **tb)
{
	size_t i;

	if (!cxt || !cxt->label || !tb)
		return -EINVAL;
	if (!cxt->label->op->get_part)
		return -ENOSYS;

	DBG(CXT, ul_debugobj(cxt, " -- get table --"));

	if (!*tb && !(*tb = fdisk_new_table()))
		return -ENOMEM;

	for (i = 0; i < cxt->label->nparts_max; i++) {
		struct fdisk_partition *pa = NULL;

		if (fdisk_get_partition(cxt, i, &pa) != 0)
			continue;
		if (fdisk_partition_is_used(pa))
			fdisk_table_add_partition(*tb, pa);
		fdisk_unref_partition(pa);
	}

	return 0;
}
