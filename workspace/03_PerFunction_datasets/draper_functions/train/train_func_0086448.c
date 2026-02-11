user_sdma_txreq_cb(struct sdma_txreq *txreq, int status,
			       int drain)
{
	struct user_sdma_txreq *tx =
		container_of(txreq, struct user_sdma_txreq, txreq);
	struct user_sdma_request *req = tx->req;
	struct hfi1_user_sdma_pkt_q *pq = req ? req->pq : NULL;
	u64 tx_seqnum;

	if (unlikely(!req || !pq))
		return;


	if (tx->idx != -1) {
		int i;

		for (i = tx->idx; i >= 0; i--) {
			if (tx->iovecs[i].flags & TXREQ_FLAGS_IOVEC_LAST_PKT)
				unpin_vector_pages(tx->iovecs[i].vec);
		}
	}

	tx_seqnum = tx->seqnum;
	kmem_cache_free(pq->txreq_cache, tx);

	if (status != SDMA_TXREQ_S_OK) {
		dd_dev_err(pq->dd, "SDMA completion with error %d", status);
		set_comp_state(req, ERROR, status);
		set_bit(SDMA_REQ_HAS_ERROR, &req->flags);


		if (tx_seqnum == ACCESS_ONCE(req->seqnum) &&
		    test_bit(SDMA_REQ_DONE_ERROR, &req->flags)) {
			atomic_dec(&pq->n_reqs);
			user_sdma_free_request(req);
		}
	} else {
		if (tx_seqnum == req->info.npkts - 1) {


			atomic_dec(&pq->n_reqs);
			set_comp_state(req, COMPLETE, 0);
			user_sdma_free_request(req);
		}
	}
	if (!atomic_read(&pq->n_reqs))
		xchg(&pq->state, SDMA_PKT_Q_INACTIVE);
}
