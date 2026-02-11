do_reset() {

	if(worker_mode == WORKER_MODE_FOREMAN) {
		work_queue_reset(foreman_q, 0);
	} else {
		kill_all_tasks();
	}

	if(delete_dir_contents(workspace) < 0) {
		return 0;
	}

	return 1;
}
