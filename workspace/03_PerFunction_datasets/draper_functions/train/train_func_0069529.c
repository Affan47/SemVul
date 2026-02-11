process_events(struct cardstate *cs)
{
	struct event_t *ev;
	unsigned head, tail;
	int i;
	int check_flags = 0;
	int was_busy;
	unsigned long flags;

	spin_lock_irqsave(&cs->ev_lock, flags);
	head = cs->ev_head;

	for (i = 0; i < 2 * MAX_EVENTS; ++i) {
		tail = cs->ev_tail;
		if (tail == head) {
			if (!check_flags && !cs->commands_pending)
				break;
			check_flags = 0;
			spin_unlock_irqrestore(&cs->ev_lock, flags);
			process_command_flags(cs);
			spin_lock_irqsave(&cs->ev_lock, flags);
			tail = cs->ev_tail;
			if (tail == head) {
				if (!cs->commands_pending)
					break;
				continue;
			}
		}

		ev = cs->events + head;
		was_busy = cs->cur_at_seq != SEQ_NONE;
		spin_unlock_irqrestore(&cs->ev_lock, flags);
		process_event(cs, ev);
		spin_lock_irqsave(&cs->ev_lock, flags);
		kfree(ev->ptr);
		ev->ptr = NULL;
		if (was_busy && cs->cur_at_seq == SEQ_NONE)
			check_flags = 1;

		head = (head + 1) % MAX_EVENTS;
		cs->ev_head = head;
	}

	spin_unlock_irqrestore(&cs->ev_lock, flags);

	if (i == 2 * MAX_EVENTS) {
		dev_err(cs->dev,
			"infinite loop in process_events; aborting.\n");
	}
}
