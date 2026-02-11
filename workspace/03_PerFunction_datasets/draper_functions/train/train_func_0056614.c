pcpdtimer_triggered(struct pcpdtimer *p)
{
	if (!p->alarm)
		return;

	if (p->prev)
		p->prev->next=p->next;
	else
		first_timer=p->next;

	if (p->next)
		p->next->prev=p->prev;
	else
		last_timer=p->prev;

	p->alarm=0;
}
