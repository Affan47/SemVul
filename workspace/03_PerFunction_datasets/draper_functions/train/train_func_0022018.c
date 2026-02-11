evtchn_unbind_from_user(struct per_user_data *u,
				    struct user_evtchn *evtchn)
{
	int irq = irq_from_evtchn(evtchn->port);

	BUG_ON(irq < 0);

	unbind_from_irqhandler(irq, evtchn);

	del_evtchn(u, evtchn);
}
