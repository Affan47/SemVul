gigaset_stop(struct cardstate *cs)
{
	mutex_lock(&cs->mutex);

	cs->waiting = 1;

	if (!gigaset_add_event(cs, &cs->at_state, EV_STOP, NULL, 0, NULL))
		goto exit;
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	cleanup_cs(cs);

exit:
	mutex_unlock(&cs->mutex);
}
