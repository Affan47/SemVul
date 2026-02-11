parq_upload_lookup_size(const struct upload *u)
{
	struct parq_ul_queued *puq;


	upload_check(u);
	puq = parq_upload_find(u);

	if (puq != NULL) {
		g_assert(puq->queue != NULL);
		return puq->queue->alive;
	} else {

		return 0;
	}
}
