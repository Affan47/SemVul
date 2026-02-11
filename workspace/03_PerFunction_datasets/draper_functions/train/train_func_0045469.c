kill_job_by_part_name(char *part_name)
{
	ListIterator job_iterator, part_iterator;
	struct job_record  *job_ptr;
	struct part_record *part_ptr, *part2_ptr;
	int job_count = 0;
	time_t now = time(NULL);

	part_ptr = find_part_record (part_name);
	if (part_ptr == NULL)
		return 0;

	job_iterator = list_iterator_create(job_list);
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		bool pending = false, suspended = false;

		pending = IS_JOB_PENDING(job_ptr);
		if (job_ptr->part_ptr_list) {

			bool rebuild_name_list = false;
			part_iterator = list_iterator_create(job_ptr->
							     part_ptr_list);
			if (part_iterator == NULL)
				fatal("list_iterator_create malloc failure");
			while ((part2_ptr = (struct part_record *)
					list_next(part_iterator))) {
				if (part2_ptr != part_ptr)
					continue;
				list_remove(part_iterator);
				rebuild_name_list = true;
			}
			list_iterator_destroy(part_iterator);
			if (rebuild_name_list) {
				if (list_count(job_ptr->part_ptr_list) > 0) {
					_rebuild_part_name_list(job_ptr);
					job_ptr->part_ptr =
						list_peek(job_ptr->
							  part_ptr_list);
				} else {
					FREE_NULL_LIST(job_ptr->part_ptr_list);
				}
			}
		}

		if (job_ptr->part_ptr != part_ptr)
			continue;

		if (IS_JOB_SUSPENDED(job_ptr)) {
			enum job_states suspend_job_state = job_ptr->job_state;


			job_ptr->job_state = JOB_CANCELLED;
			jobacct_storage_g_job_suspend(acct_db_conn, job_ptr);
			job_ptr->job_state = suspend_job_state;
			suspended = true;
		}
		if (IS_JOB_RUNNING(job_ptr) || suspended) {
			job_count++;
			info("Killing job_id %u on defunct partition %s",
			     job_ptr->job_id, part_name);
			job_ptr->job_state = JOB_NODE_FAIL | JOB_COMPLETING;
			build_cg_bitmap(job_ptr);
			job_ptr->exit_code = MAX(job_ptr->exit_code, 1);
			job_ptr->state_reason = FAIL_DOWN_PARTITION;
			xfree(job_ptr->state_desc);
			if (suspended) {
				job_ptr->end_time = job_ptr->suspend_time;
				job_ptr->tot_sus_time +=
					difftime(now, job_ptr->suspend_time);
			} else
				job_ptr->end_time = now;
			job_completion_logger(job_ptr, false);
			if (!pending)
				deallocate_nodes(job_ptr, false, suspended,
						 false);
		} else if (pending) {
			job_count++;
			info("Killing job_id %u on defunct partition %s",
			     job_ptr->job_id, part_name);
			job_ptr->job_state	= JOB_CANCELLED;
			job_ptr->start_time	= now;
			job_ptr->end_time	= now;
			job_ptr->exit_code	= 1;
			job_completion_logger(job_ptr, false);
		}
		job_ptr->part_ptr = NULL;
		FREE_NULL_LIST(job_ptr->part_ptr_list);
	}
	list_iterator_destroy(job_iterator);

	if (job_count)
		last_job_update = now;
	return job_count;
}
