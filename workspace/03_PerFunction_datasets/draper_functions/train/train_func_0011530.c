mad_error_handler(struct ib_mad_port_private *port_priv,
			      struct ib_wc *wc)
{
	struct ib_mad_list_head *mad_list;
	struct ib_mad_qp_info *qp_info;
	struct ib_mad_send_wr_private *mad_send_wr;
	int ret;


	mad_list = (struct ib_mad_list_head *)(unsigned long)wc->wr_id;
	qp_info = mad_list->mad_queue->qp_info;
	if (mad_list->mad_queue == &qp_info->recv_queue)


		return;


	mad_send_wr = container_of(mad_list, struct ib_mad_send_wr_private,
				   mad_list);
	if (wc->status == IB_WC_WR_FLUSH_ERR) {
		if (mad_send_wr->retry) {

			struct ib_send_wr *bad_send_wr;

			mad_send_wr->retry = 0;
			ret = ib_post_send(qp_info->qp, &mad_send_wr->send_wr.wr,
					&bad_send_wr);
			if (ret)
				ib_mad_send_done_handler(port_priv, wc);
		} else
			ib_mad_send_done_handler(port_priv, wc);
	} else {
		struct ib_qp_attr *attr;


		attr = kmalloc(sizeof *attr, GFP_KERNEL);
		if (attr) {
			attr->qp_state = IB_QPS_RTS;
			attr->cur_qp_state = IB_QPS_SQE;
			ret = ib_modify_qp(qp_info->qp, attr,
					   IB_QP_STATE | IB_QP_CUR_STATE);
			kfree(attr);
			if (ret)
				dev_err(&port_priv->device->dev,
					"mad_error_handler - ib_modify_qp to RTS : %d\n",
					ret);
			else
				mark_sends_for_retry(qp_info);
		}
		ib_mad_send_done_handler(port_priv, wc);
	}
}
