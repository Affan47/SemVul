reclaimable(const struct sge_txq *tq)
{
	int hw_cidx = be16_to_cpu(tq->stat->cidx);
	int reclaimable = hw_cidx - tq->cidx;
	if (reclaimable < 0)
		reclaimable += tq->size;
	return reclaimable;
}
