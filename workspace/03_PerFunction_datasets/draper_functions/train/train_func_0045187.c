deactivate_tqueue(tqueue * tq)
{
    tq->usage = NO_USAGE;

    tq->next = idle_tqueues;
    tq->prev = &idle_tqueues;
    if (idle_tqueues)
	idle_tqueues->prev = &(tq->next);
    idle_tqueues = tq;
}
