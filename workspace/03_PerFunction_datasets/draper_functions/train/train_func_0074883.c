reclaim_completed_tx(struct adapter *adapter,
						struct sge_txq *q,
						unsigned int chunk)
{
	unsigned int reclaim = q->processed - q->cleaned;

	reclaim = min(chunk, reclaim);
	if (reclaim) {
		free_tx_desc(adapter, q, reclaim);
		q->cleaned += reclaim;
		q->in_use -= reclaim;
	}
	return q->processed - q->cleaned;
}
