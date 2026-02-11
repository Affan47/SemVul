cfq_update_hw_tag(struct cfq_data *cfqd)
{
	struct cfq_queue *cfqq = cfqd->active_queue;

	if (cfqd->rq_in_driver > cfqd->hw_tag_est_depth)
		cfqd->hw_tag_est_depth = cfqd->rq_in_driver;

	if (cfqd->hw_tag == 1)
		return;

	if (cfqd->rq_queued <= CFQ_HW_QUEUE_MIN &&
	    cfqd->rq_in_driver <= CFQ_HW_QUEUE_MIN)
		return;


	if (cfqq && cfq_cfqq_idle_window(cfqq) &&
	    cfqq->dispatched + cfqq->queued[0] + cfqq->queued[1] <
	    CFQ_HW_QUEUE_MIN && cfqd->rq_in_driver < CFQ_HW_QUEUE_MIN)
		return;

	if (cfqd->hw_tag_samples++ < 50)
		return;

	if (cfqd->hw_tag_est_depth >= CFQ_HW_QUEUE_MIN)
		cfqd->hw_tag = 1;
	else
		cfqd->hw_tag = 0;
}
