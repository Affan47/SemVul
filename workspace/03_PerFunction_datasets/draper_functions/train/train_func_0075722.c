set_pool_mode(struct pool *pool, enum pool_mode new_mode)
{
	struct pool_c *pt = pool->ti->private;
	bool needs_check = dm_pool_metadata_needs_check(pool->pmd);
	enum pool_mode old_mode = get_pool_mode(pool);
	unsigned long no_space_timeout = ACCESS_ONCE(no_space_timeout_secs) * HZ;


	if (new_mode == PM_WRITE && needs_check) {
		DMERR("%s: unable to switch pool to write mode until repaired.",
		      dm_device_name(pool->pool_md));
		if (old_mode != new_mode)
			new_mode = old_mode;
		else
			new_mode = PM_READ_ONLY;
	}


	if (old_mode == PM_FAIL)
		new_mode = old_mode;

	switch (new_mode) {
	case PM_FAIL:
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "failure");
		dm_pool_metadata_read_only(pool->pmd);
		pool->process_bio = process_bio_fail;
		pool->process_discard = process_bio_fail;
		pool->process_cell = process_cell_fail;
		pool->process_discard_cell = process_cell_fail;
		pool->process_prepared_mapping = process_prepared_mapping_fail;
		pool->process_prepared_discard = process_prepared_discard_fail;

		error_retry_list(pool);
		break;

	case PM_READ_ONLY:
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "read-only");
		dm_pool_metadata_read_only(pool->pmd);
		pool->process_bio = process_bio_read_only;
		pool->process_discard = process_bio_success;
		pool->process_cell = process_cell_read_only;
		pool->process_discard_cell = process_cell_success;
		pool->process_prepared_mapping = process_prepared_mapping_fail;
		pool->process_prepared_discard = process_prepared_discard_success;

		error_retry_list(pool);
		break;

	case PM_OUT_OF_DATA_SPACE:


		if (old_mode != new_mode)
			notify_of_pool_mode_change_to_oods(pool);
		pool->process_bio = process_bio_read_only;
		pool->process_discard = process_discard_bio;
		pool->process_cell = process_cell_read_only;
		pool->process_prepared_mapping = process_prepared_mapping;
		set_discard_callbacks(pool);

		if (!pool->pf.error_if_no_space && no_space_timeout)
			queue_delayed_work(pool->wq, &pool->no_space_timeout, no_space_timeout);
		break;

	case PM_WRITE:
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "write");
		pool->pf.error_if_no_space = pt->requested_pf.error_if_no_space;
		dm_pool_metadata_read_write(pool->pmd);
		pool->process_bio = process_bio;
		pool->process_discard = process_discard_bio;
		pool->process_cell = process_cell;
		pool->process_prepared_mapping = process_prepared_mapping;
		set_discard_callbacks(pool);
		break;
	}

	pool->pf.mode = new_mode;


	pt->adjusted_pf.mode = new_mode;
}
