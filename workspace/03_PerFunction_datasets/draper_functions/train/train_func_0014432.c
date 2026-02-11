scif_teardown_ep(void *endpt)
{
	struct scif_endpt *ep = endpt;
	struct scif_qp *qp = ep->qp_info.qp;

	if (qp) {
		spin_lock(&ep->lock);
		scif_cleanup_ep_qp(ep);
		spin_unlock(&ep->lock);
		kfree(qp->inbound_q.rb_base);
		kfree(qp);
	}
}
