scif_setup_loopback_qp(struct scif_dev *scifdev)
{
	int err = 0;
	void *local_q;
	struct scif_qp *qp;

	err = scif_setup_intr_wq(scifdev);
	if (err)
		goto exit;
	INIT_LIST_HEAD(&scif_info.loopb_recv_q);
	snprintf(scif_info.loopb_wqname, sizeof(scif_info.loopb_wqname),
		 "SCIF LOOPB %d", scifdev->node);
	scif_info.loopb_wq =
		alloc_ordered_workqueue(scif_info.loopb_wqname, 0);
	if (!scif_info.loopb_wq) {
		err = -ENOMEM;
		goto destroy_intr;
	}
	INIT_WORK(&scif_info.loopb_work, scif_loopb_wq_handler);

	scifdev->qpairs = kzalloc(sizeof(*scifdev->qpairs), GFP_KERNEL);
	if (!scifdev->qpairs) {
		err = -ENOMEM;
		goto destroy_loopb_wq;
	}

	qp = scifdev->qpairs;
	qp->magic = SCIFEP_MAGIC;
	spin_lock_init(&qp->send_lock);
	spin_lock_init(&qp->recv_lock);

	local_q = kzalloc(SCIF_NODE_QP_SIZE, GFP_KERNEL);
	if (!local_q) {
		err = -ENOMEM;
		goto free_qpairs;
	}


	scif_rb_init(&qp->outbound_q,
		     &qp->local_read,
		     &qp->local_write,
		     local_q, get_count_order(SCIF_NODE_QP_SIZE));

	scif_rb_init(&qp->inbound_q,
		     &qp->local_read,
		     &qp->local_write,
		     local_q, get_count_order(SCIF_NODE_QP_SIZE));
	scif_info.nodeid = scifdev->node;

	scif_peer_register_device(scifdev);

	scif_info.loopb_dev = scifdev;
	return err;
free_qpairs:
	kfree(scifdev->qpairs);
destroy_loopb_wq:
	destroy_workqueue(scif_info.loopb_wq);
destroy_intr:
	scif_destroy_intr_wq(scifdev);
exit:
	return err;
}
