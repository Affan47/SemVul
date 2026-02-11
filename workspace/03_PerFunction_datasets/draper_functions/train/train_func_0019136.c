brcmu_pktq_flush(struct pktq *pq, bool dir,
		      bool (*fn)(struct sk_buff *, void *), void *arg)
{
	int prec;
	for (prec = 0; prec < pq->num_prec; prec++)
		brcmu_pktq_pflush(pq, prec, dir, fn, arg);
}
