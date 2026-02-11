parq_upload_frozen_clear(struct parq_ul_queued *puq)
{
	parq_ul_queued_check(puq);
	g_assert(puq->flags & PARQ_UL_FROZEN);

	puq->flags &= ~PARQ_UL_FROZEN;

	g_assert(puq->by_addr->frozen > 0);
	g_assert(puq->queue->frozen > 0);

	puq->by_addr->frozen--;
	puq->queue->frozen--;
}
