start_update_threading(void)
{
	struct update_cb *uc;

	threading_started = 1;

	for (uc = update_cb_head.next; uc; uc = uc->next) {
		if (!uc->running) {
			uc->running = 1;
			pthread_create(&uc->thread, NULL, &run_update_callback, uc);
		}
	}
}
