pulse_queue_dequeue(struct pri_detector *pde)
{
	struct pulse_elem *p = pulse_queue_get_tail(pde);
	if (p != NULL) {
		list_del_init(&p->head);
		pde->count--;

		pool_put_pulse_elem(p);
	}
	return (pde->count > 0);
}
