phm_construct_table(struct pp_hwmgr *hwmgr,
			struct phm_master_table_header *master_table,
			struct phm_runtime_table_header *rt_table)
{
	uint32_t function_count = 0;
	const struct phm_master_table_item *table_item;
	uint32_t size;
	phm_table_function *run_time_list;
	phm_table_function *rtf;

	if (hwmgr == NULL || master_table == NULL || rt_table == NULL) {
		printk(KERN_ERR "[ powerplay ] Invalid Parameter!\n");
		return -EINVAL;
	}

	for (table_item = master_table->master_list;
		NULL != table_item->tableFunction; table_item++) {
		if ((NULL == table_item->isFunctionNeededInRuntimeTable) ||
		    (table_item->isFunctionNeededInRuntimeTable(hwmgr)))
			function_count++;
	}

	size = (function_count + 1) * sizeof(phm_table_function);
	run_time_list = kzalloc(size, GFP_KERNEL);

	if (NULL == run_time_list)
		return -ENOMEM;

	rtf = run_time_list;
	for (table_item = master_table->master_list;
		NULL != table_item->tableFunction; table_item++) {
		if ((rtf - run_time_list) > function_count) {
			printk(KERN_ERR "[ powerplay ] Check function results have changed\n");
			kfree(run_time_list);
			return -EINVAL;
		}

		if ((NULL == table_item->isFunctionNeededInRuntimeTable) ||
		     (table_item->isFunctionNeededInRuntimeTable(hwmgr))) {
			*(rtf++) = table_item->tableFunction;
		}
	}

	if ((rtf - run_time_list) > function_count) {
		printk(KERN_ERR "[ powerplay ] Check function results have changed\n");
		kfree(run_time_list);
		return -EINVAL;
	}

	*rtf = NULL;
	rt_table->function_list = run_time_list;
	rt_table->exit_error = (0 != (master_table->flags & PHM_MasterTableFlag_ExitOnError));
	rt_table->storage_size = master_table->storage_size;
	return 0;
}
