user_sdma_free_request(struct user_sdma_request *req)
{
	if (!list_empty(&req->txps)) {
		struct sdma_txreq *t, *p;

		list_for_each_entry_safe(t, p, &req->txps, list) {
			struct user_sdma_txreq *tx =
				container_of(t, struct user_sdma_txreq, txreq);
			list_del_init(&t->list);
			sdma_txclean(req->pq->dd, t);
			kmem_cache_free(req->pq->txreq_cache, tx);
		}
	}
	if (req->data_iovs) {
		int i;

		for (i = 0; i < req->data_iovs; i++)
			if (req->iovs[i].npages && req->iovs[i].pages)
				unpin_vector_pages(&req->iovs[i]);
	}
	if (req->user_proc)
		put_task_struct(req->user_proc);
	kfree(req->tids);
	clear_bit(SDMA_REQ_IN_USE, &req->flags);
}
