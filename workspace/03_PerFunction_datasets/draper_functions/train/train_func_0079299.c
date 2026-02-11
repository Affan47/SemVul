mono_lock_free_queue_dequeue (MonoLockFreeQueue *q)
{
	MonoThreadHazardPointers *hp = mono_hazard_pointer_get ();
	MonoLockFreeQueueNode *head;

 retry:
	for (;;) {
		MonoLockFreeQueueNode *tail, *next;

		head = get_hazardous_pointer ((gpointer volatile*)&q->head, hp, 0);
		tail = (MonoLockFreeQueueNode*)q->tail;
		mono_memory_read_barrier ();
		next = head->next;
		mono_memory_read_barrier ();


		if (head == q->head) {
			g_assert (next != INVALID_NEXT && next != FREE_NEXT);
			g_assert (next != head);


			if (head == tail) {
				if (next == END_MARKER) {

					mono_hazard_pointer_clear (hp, 0);


					if (!is_dummy (q, head) && try_reenqueue_dummy (q))
						continue;

					return NULL;
				}


				InterlockedCompareExchangePointer ((gpointer volatile*)&q->tail, next, tail);
			} else {
				g_assert (next != END_MARKER);

				if (InterlockedCompareExchangePointer ((gpointer volatile*)&q->head, next, head) == head)
					break;
			}
		}

		mono_memory_write_barrier ();
		mono_hazard_pointer_clear (hp, 0);
	}


	mono_memory_write_barrier ();
	mono_hazard_pointer_clear (hp, 0);

	g_assert (head->next);


	head->next = INVALID_NEXT;
#if QUEUE_DEBUG
	g_assert (head->in_queue);
	head->in_queue = FALSE;
	mono_memory_write_barrier ();
#endif

	if (is_dummy (q, head)) {
		g_assert (q->has_dummy);
		q->has_dummy = 0;
		mono_memory_write_barrier ();
		mono_thread_hazardous_free_or_queue (head, free_dummy, FALSE, TRUE);
		if (try_reenqueue_dummy (q))
			goto retry;
		return NULL;
	}


	return head;
}
