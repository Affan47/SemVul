dq_kept_results(dquery_t *dq)
{
	dquery_check(dq);


	if (dq->flags & DQ_F_LOCAL)
		return dq->kept_results = search_get_kept_results_by_handle(dq->sh);


	return (dq->flags & DQ_F_GOT_GUIDANCE) ?
		(dq->kept_results / DQ_AVG_ULTRA_NODES) + dq->new_results :
		dq->results;
}
