execute_work()
{
	struct tgt_work *work, *n;

	list_for_each_entry_safe(work, n, &inactive_work_list, entry) {
		if (before(elapsed_msecs, work->when))
			break;

		list_del(&work->entry);
		list_add_tail(&work->entry, &active_work_list);
	}

	while (!list_empty(&active_work_list)) {
		work = list_first_entry(&active_work_list,
					struct tgt_work, entry);
		list_del_init(&work->entry);
		work->func(work->data);
	}
}
