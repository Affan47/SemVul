reclaimable(const struct sge_txq *q)
{
	int hw_cidx = ntohs(q->stat->cidx);
	hw_cidx -= q->cidx;
	return hw_cidx < 0 ? hw_cidx + q->size : hw_cidx;
}
