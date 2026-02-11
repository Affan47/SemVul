dump_waitq(ulong wq, char *wq_name)
{
	struct list_data list_data, *ld;
	ulong *wq_list;
	ulong next_offset;
	ulong task_offset;
	int cnt;
	int start_index;
	int i;

	ld = &list_data;
	BZERO(ld, sizeof(*ld));


	if (VALID_STRUCT(wait_queue)) {
		task_offset = OFFSET(wait_queue_task);
		next_offset = OFFSET(wait_queue_next);
		ld->end = wq;
		ld->start = wq;
		ld->member_offset = next_offset;
		ld->list_head_offset = task_offset;

		start_index = 0;
	} else if (VALID_STRUCT(__wait_queue)) {
		ulong task_list_offset;

                next_offset = OFFSET(list_head_next);
                task_offset = OFFSET(__wait_queue_task);
                task_list_offset = OFFSET(__wait_queue_head_task_list);
                ld->end = ld->start = wq + task_list_offset + next_offset;
                ld->list_head_offset = OFFSET(__wait_queue_task_list);
                ld->member_offset = next_offset;

		start_index = 1;
	} else {
		return;
	}

	hq_open();

	cnt = do_list(ld);
	if (cnt <= 1) {


		if (wq_name)
			fprintf(fp, "wait queue \"%s\" (%lx) is empty\n",
				wq_name, wq);
		else
			fprintf(fp, "wait queue %lx is empty\n", wq);
		hq_close();
		return;
	}

	wq_list = (ulong *) GETBUF(cnt * sizeof(ulong));
	cnt = retrieve_list(wq_list, cnt);

	for (i = start_index; i < cnt; i++) {
		struct task_context *tc;
		ulong task;

		readmem(wq_list[i] + task_offset, KVADDR, &task,
			sizeof(void *), "wait_queue_t.task", FAULT_ON_ERROR);

		if ((tc = task_to_context(task))) {
			print_task_header(fp, tc, 0);
		} else {
			break;
		}
	}

	hq_close();
}
