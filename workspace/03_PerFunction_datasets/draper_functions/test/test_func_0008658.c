at_state_invalid(struct cardstate *cs,
			    struct at_state_t *test_ptr)
{
	unsigned long flags;
	unsigned channel;
	struct at_state_t *at_state;
	int retval = 0;

	spin_lock_irqsave(&cs->lock, flags);

	if (test_ptr == &cs->at_state)
		goto exit;

	list_for_each_entry(at_state, &cs->temp_at_states, list)
		if (at_state == test_ptr)
			goto exit;

	for (channel = 0; channel < cs->channels; ++channel)
		if (&cs->bcs[channel].at_state == test_ptr)
			goto exit;

	retval = 1;
exit:
	spin_unlock_irqrestore(&cs->lock, flags);
	return retval;
}
