qib7322_poll_cq ( struct ib_device *ibdev,
			      struct ib_completion_queue *cq ) {
	struct ib_work_queue *wq;


	list_for_each_entry ( wq, &cq->work_queues, list ) {
		if ( wq->is_send ) {
			qib7322_poll_send_wq ( ibdev, wq->qp );
		} else {
			qib7322_poll_recv_wq ( ibdev, wq->qp );
		}
	}
}
