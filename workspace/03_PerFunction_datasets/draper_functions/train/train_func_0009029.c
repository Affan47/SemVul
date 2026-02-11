wait_on_ctr_state(struct capi_ctr *ctr, unsigned int state)
{
	DEFINE_WAIT(wait);
	int retval = 0;

	ctr = capi_ctr_get(ctr);
	if (!ctr)
		return -ESRCH;

	for (;;) {
		prepare_to_wait(&ctr->state_wait_queue, &wait,
				TASK_INTERRUPTIBLE);

		if (ctr->state == state)
			break;
		if (ctr->state == CAPI_CTR_DETACHED) {
			retval = -ESRCH;
			break;
		}
		if (signal_pending(current)) {
			retval = -EINTR;
			break;
		}

		mutex_unlock(&capi_controller_lock);
		schedule();
		mutex_lock(&capi_controller_lock);
	}
	finish_wait(&ctr->state_wait_queue, &wait);

	capi_ctr_put(ctr);

	return retval;
}
