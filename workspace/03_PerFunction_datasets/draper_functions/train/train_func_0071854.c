sysrq_reinject_alt_sysrq(struct work_struct *work)
{
	struct sysrq_state *sysrq =
			container_of(work, struct sysrq_state, reinject_work);
	struct input_handle *handle = &sysrq->handle;
	unsigned int alt_code = sysrq->alt_use;

	if (sysrq->need_reinject) {

		sysrq->reinjecting = true;
		mb();


		input_inject_event(handle, EV_KEY, alt_code, 1);
		input_inject_event(handle, EV_KEY, KEY_SYSRQ, 1);
		input_inject_event(handle, EV_SYN, SYN_REPORT, 1);

		input_inject_event(handle, EV_KEY, KEY_SYSRQ, 0);
		input_inject_event(handle, EV_KEY, alt_code, 0);
		input_inject_event(handle, EV_SYN, SYN_REPORT, 1);

		mb();
		sysrq->reinjecting = false;
	}
}
