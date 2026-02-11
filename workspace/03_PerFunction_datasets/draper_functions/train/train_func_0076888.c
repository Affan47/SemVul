aev_insert(aev_port_t *evp, aev_event_t *ev)
{
EVDBG(log_printf(D2LOG, "aev_insert:\n");)
	if(!evp->first)
	{
EVDBG(log_printf(D2LOG, "  empty list\n");)
		ev->next = NULL;
		evp->first = evp->last = ev;
	}
	else if((Sint16)(evp->last->frame - ev->frame) <= 0)
	{
EVDBG(log_printf(D2LOG, "  last\n");)
		ev->next = NULL;
		evp->last->next = ev;
		evp->last = ev;
	}
	else
	{
		aev_event_t *e_prev = NULL;
		aev_event_t *e = evp->first;
EVDBG(log_printf(D2LOG, " scanning...\n");)
		while((Sint16)(e->frame - ev->frame) <= 0)
		{
EVDBG(log_printf(D2LOG, "e->frame = %d, ev->frame = %d\n", e->frame, ev->frame);)
			e_prev = e;
			e = e->next;
		}
		ev->next = e;
		if(e_prev)
		{
EVDBG(log_printf(D2LOG, "  insert\n");)
			e_prev->next = ev;
		}
		else
		{
EVDBG(log_printf(D2LOG, "  first\n");)
			evp->first = ev;
		}
	}
#ifdef AEV_TRACKING
	ev->port = evp;
#endif
}
