scif_cnctreq(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = NULL;
	struct scif_conreq *conreq;

	conreq = kmalloc(sizeof(*conreq), GFP_KERNEL);
	if (!conreq)

		goto conreq_sendrej;

	ep = scif_find_listen_ep(msg->dst.port);
	if (!ep)

		goto conreq_sendrej_free;
	else
		spin_lock(&ep->lock);

	if (ep->backlog <= ep->conreqcnt) {

		spin_unlock(&ep->lock);
		goto conreq_sendrej_free;
	}

	conreq->msg = *msg;
	list_add_tail(&conreq->list, &ep->conlist);
	ep->conreqcnt++;
	wake_up_interruptible(&ep->conwq);
	spin_unlock(&ep->lock);
	return;

conreq_sendrej_free:
	kfree(conreq);
conreq_sendrej:
	msg->uop = SCIF_CNCT_REJ;
	scif_nodeqp_send(&scif_dev[msg->src.node], msg);
}
