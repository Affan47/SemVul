qib_user_sdma_init_payload(const struct qib_devdata *dd,
				      struct qib_user_sdma_queue *pq,
				      struct qib_user_sdma_pkt *pkt,
				      const struct iovec *iov,
				      unsigned long niov, int npages)
{
	int ret = 0;

	if (pkt->frag_size == pkt->bytes_togo &&
			npages >= ARRAY_SIZE(pkt->addr))
		ret = qib_user_sdma_coalesce(dd, pq, pkt, iov, niov);
	else
		ret = qib_user_sdma_pin_pkt(dd, pq, pkt, iov, niov);

	return ret;
}
