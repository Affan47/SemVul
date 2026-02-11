brcmu_pktq_mdeq(struct pktq *pq, uint prec_bmp,
				      int *prec_out)
{
	struct sk_buff_head *q;
	struct sk_buff *p;
	int prec;

	if (pq->len == 0)
		return NULL;

	while ((prec = pq->hi_prec) > 0 &&
	       skb_queue_empty(&pq->q[prec].skblist))
		pq->hi_prec--;

	while ((prec_bmp & (1 << prec)) == 0 ||
	       skb_queue_empty(&pq->q[prec].skblist))
		if (prec-- == 0)
			return NULL;

	q = &pq->q[prec].skblist;
	p = skb_dequeue(q);
	if (p == NULL)
		return NULL;

	pq->len--;

	if (prec_out)
		*prec_out = prec;

	return p;
}
