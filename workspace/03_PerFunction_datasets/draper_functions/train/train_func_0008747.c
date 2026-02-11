clear_events(struct cardstate *cs)
{
	struct event_t *ev;
	unsigned head, tail;
	unsigned long flags;

	spin_lock_irqsave(&cs->ev_lock, flags);

	head = cs->ev_head;
	tail = cs->ev_tail;

	while (tail != head) {
		ev = cs->events + head;
		kfree(ev->ptr);
		head = (head + 1) % MAX_EVENTS;
	}

	cs->ev_head = tail;

	spin_unlock_irqrestore(&cs->ev_lock, flags);
}
