pcpdtimer_install(struct pcpdtimer *p, time_t nseconds)
{
	struct pcpdtimer *q;

	if (p->alarm)
	{
		if (p->prev)
			p->prev->next=p->next;
		else
			first_timer=p->next;

		if (p->next)
			p->next->prev=p->prev;
		else
			last_timer=p->prev;
	}

	time(&p->alarm);
	p->alarm += nseconds;

	for (q=first_timer; q; q=q->next)
	{
		if (q->alarm > p->alarm)
			break;
	}

	if (!q)
	{
		if ((p->prev=last_timer) != 0)
			p->prev->next=p;
		else
			first_timer=p;
		p->next=0;
		last_timer=p;
	}
	else
	{
		if ((p->prev=q->prev) != 0)
			p->prev->next=p;
		else
			first_timer=p;

		p->next=q;
		q->prev=p;
	}
}
