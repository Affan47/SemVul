_scif_send(scif_epd_t epd, void *msg, int len, int flags)
{
	struct scif_endpt *ep = (struct scif_endpt *)epd;
	struct scifmsg notif_msg;
	int curr_xfer_len = 0, sent_len = 0, write_count;
	int ret = 0;
	struct scif_qp *qp = ep->qp_info.qp;

	if (flags & SCIF_SEND_BLOCK)
		might_sleep();

	spin_lock(&ep->lock);
	while (sent_len != len && SCIFEP_CONNECTED == ep->state) {
		write_count = scif_rb_space(&qp->outbound_q);
		if (write_count) {

			curr_xfer_len = min(len - sent_len, write_count);
			ret = scif_rb_write(&qp->outbound_q, msg,
					    curr_xfer_len);
			if (ret < 0)
				break;

			scif_rb_commit(&qp->outbound_q);


			notif_msg.src = ep->port;
			notif_msg.uop = SCIF_CLIENT_SENT;
			notif_msg.payload[0] = ep->remote_ep;
			ret = _scif_nodeqp_send(ep->remote_dev, &notif_msg);
			if (ret)
				break;
			sent_len += curr_xfer_len;
			msg = msg + curr_xfer_len;
			continue;
		}
		curr_xfer_len = min(len - sent_len, SCIF_ENDPT_QP_SIZE - 1);

		if (!(flags & SCIF_SEND_BLOCK))
			break;

		spin_unlock(&ep->lock);

		ret =
		wait_event_interruptible(ep->sendwq,
					 (SCIFEP_CONNECTED != ep->state) ||
					 (scif_rb_space(&qp->outbound_q) >=
					 curr_xfer_len));
		spin_lock(&ep->lock);
		if (ret)
			break;
	}
	if (sent_len)
		ret = sent_len;
	else if (!ret && SCIFEP_CONNECTED != ep->state)
		ret = SCIFEP_DISCONNECTED == ep->state ?
			-ECONNRESET : -ENOTCONN;
	spin_unlock(&ep->lock);
	return ret;
}
