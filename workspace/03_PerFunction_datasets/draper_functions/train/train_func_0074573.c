cfq_put_request(struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	if (cfqq) {
		const int rw = rq_data_dir(rq);

		BUG_ON(!cfqq->allocated[rw]);
		cfqq->allocated[rw]--;


		cfqg_put(RQ_CFQG(rq));
		rq->elv.priv[0] = NULL;
		rq->elv.priv[1] = NULL;

		cfq_put_queue(cfqq);
	}
}
