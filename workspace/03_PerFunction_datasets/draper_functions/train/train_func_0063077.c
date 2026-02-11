t5_start_event(isc_task_t *task, isc_event_t *event) {
	isc_result_t	isc_result;

	UNUSED(task);

	t_info("t5_start_event\n");

	isc_result = isc_mutex_lock(&T5_mx);
	if (isc_result != ISC_R_SUCCESS) {
		t_info("isc_mutex_lock failed %s\n",
		       isc_result_totext(isc_result));
		++T5_nprobs;
	}

	while (! T5_startflag) {
		(void) isc_condition_wait(&T5_cv, &T5_mx);
	}

	isc_result = isc_mutex_unlock(&T5_mx);
	if (isc_result != ISC_R_SUCCESS) {
		t_info("isc_mutex_unlock failed %s\n",
		       isc_result_totext(isc_result));
		++T5_nprobs;
	}
	isc_event_free(&event);
}
