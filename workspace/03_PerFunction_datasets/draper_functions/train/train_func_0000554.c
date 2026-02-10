_pick_idle_node_cnt(bitstr_t *avail_bitmap,
				     resv_desc_msg_t *resv_desc_ptr,
				     uint32_t node_cnt, bitstr_t **core_bitmap)
{
	ListIterator job_iterator;
	struct job_record *job_ptr;
	bitstr_t *save_bitmap, *ret_bitmap, *tmp_bitmap;

	if (bit_set_count(avail_bitmap) < node_cnt) {
		verbose("reservation requests more nodes than are available");
		return NULL;
	}

	save_bitmap = bit_copy(avail_bitmap);
	bit_or(avail_bitmap, save_bitmap);
	job_iterator = list_iterator_create(job_list);
	if (job_iterator == NULL)
		fatal("list_iterator_create: malloc failure");

	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (!IS_JOB_RUNNING(job_ptr) && !IS_JOB_SUSPENDED(job_ptr))
			continue;
		if (job_ptr->end_time < resv_desc_ptr->start_time)
			continue;

		if (resv_desc_ptr->core_cnt == 0) {
			bit_not(job_ptr->node_bitmap);
			bit_and(avail_bitmap, job_ptr->node_bitmap);
			bit_not(job_ptr->node_bitmap);
		} else {
			_check_job_compatibility(job_ptr, avail_bitmap,
						 core_bitmap);
		}
	}

	list_iterator_destroy(job_iterator);
	ret_bitmap = select_g_resv_test(avail_bitmap, node_cnt,
					resv_desc_ptr->core_cnt, core_bitmap);
	if (ret_bitmap)
		goto fini;


	if (resv_desc_ptr->flags & RESERVE_FLAG_IGN_JOBS) {
		job_iterator = list_iterator_create(job_list);
		if (!job_iterator)
			fatal("list_iterator_create: malloc failure");
		while ((job_ptr = (struct job_record *)
			list_next(job_iterator))) {
			if (!IS_JOB_RUNNING(job_ptr) &&
			    !IS_JOB_SUSPENDED(job_ptr))
				continue;
			if (job_ptr->end_time < resv_desc_ptr->start_time)
				continue;
			tmp_bitmap = bit_copy(save_bitmap);
			bit_and(tmp_bitmap, job_ptr->node_bitmap);
			if (bit_set_count(tmp_bitmap) > 0) {
				bit_or(avail_bitmap, tmp_bitmap);
				ret_bitmap = select_g_resv_test(avail_bitmap,
						node_cnt,
						resv_desc_ptr->core_cnt,
						core_bitmap);
			}
			FREE_NULL_BITMAP(tmp_bitmap);
			if (ret_bitmap)
				break;
		}
		list_iterator_destroy(job_iterator);
	}

fini:	FREE_NULL_BITMAP(save_bitmap);
#if 0
	if (ret_bitmap) {
		char str[300];
		bit_fmt(str, (sizeof(str) - 1), ret_bitmap);
		info("pick_idle_nodes getting %s from select cons_res", str);
		if (*core_bitmap) {
			bit_fmt(str, (sizeof(str) - 1), *core_bitmap);
			info("pick_idle_nodes getting core_cnt:%d coremap:%s "
			     "from select/cons_res",
			     resv_desc_ptr->core_cnt, str);
		}
	}
#endif
	return ret_bitmap;
}
