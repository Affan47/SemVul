log_shutdown(void)

{
	log_group_t*	group;

	group = UT_LIST_GET_FIRST(log_sys->log_groups);

	while (UT_LIST_GET_LEN(log_sys->log_groups) > 0) {
		log_group_t*	prev_group = group;

		group = UT_LIST_GET_NEXT(log_groups, group);
		UT_LIST_REMOVE(log_groups, log_sys->log_groups, prev_group);

		log_group_close(prev_group);
	}

	mem_free(log_sys->buf_ptr);
	log_sys->buf_ptr = NULL;
	log_sys->buf = NULL;
	mem_free(log_sys->checkpoint_buf_ptr);
	log_sys->checkpoint_buf_ptr = NULL;
	log_sys->checkpoint_buf = NULL;

	os_event_free(log_sys->no_flush_event);
	os_event_free(log_sys->one_flushed_event);

	rw_lock_free(&log_sys->checkpoint_lock);

	mutex_free(&log_sys->mutex);

#ifdef UNIV_LOG_ARCHIVE
	rw_lock_free(&log_sys->archive_lock);
	os_event_create(log_sys->archiving_on);
#endif

#ifdef UNIV_LOG_DEBUG
	recv_sys_debug_free();
#endif

	recv_sys_close();
}
