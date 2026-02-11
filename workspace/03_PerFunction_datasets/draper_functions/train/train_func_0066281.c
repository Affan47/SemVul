ib_mad_complete_recv(struct ib_mad_agent_private *mad_agent_priv,
				 struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_mad_send_wr_private *mad_send_wr;
	struct ib_mad_send_wc mad_send_wc;
	unsigned long flags;

	INIT_LIST_HEAD(&mad_recv_wc->rmpp_list);
	list_add(&mad_recv_wc->recv_buf.list, &mad_recv_wc->rmpp_list);
	if (ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)) {
		mad_recv_wc = ib_process_rmpp_recv_wc(mad_agent_priv,
						      mad_recv_wc);
		if (!mad_recv_wc) {
			deref_mad_agent(mad_agent_priv);
			return;
		}
	}


	if (ib_response_mad(&mad_recv_wc->recv_buf.mad->mad_hdr)) {
		spin_lock_irqsave(&mad_agent_priv->lock, flags);
		mad_send_wr = ib_find_send_mad(mad_agent_priv, mad_recv_wc);
		if (!mad_send_wr) {
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
			if (!ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)
			   && ib_is_mad_class_rmpp(mad_recv_wc->recv_buf.mad->mad_hdr.mgmt_class)
			   && (ib_get_rmpp_flags(&((struct ib_rmpp_mad *)mad_recv_wc->recv_buf.mad)->rmpp_hdr)
					& IB_MGMT_RMPP_FLAG_ACTIVE)) {


				mad_recv_wc->wc->wr_id = 0;
				mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent,
								   mad_recv_wc);
				atomic_dec(&mad_agent_priv->refcount);
			} else {


				ib_free_recv_mad(mad_recv_wc);
				deref_mad_agent(mad_agent_priv);
				return;
			}
		} else {
			ib_mark_mad_done(mad_send_wr);
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);


			mad_recv_wc->wc->wr_id = (unsigned long) &mad_send_wr->send_buf;
			mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent,
							   mad_recv_wc);
			atomic_dec(&mad_agent_priv->refcount);

			mad_send_wc.status = IB_WC_SUCCESS;
			mad_send_wc.vendor_err = 0;
			mad_send_wc.send_buf = &mad_send_wr->send_buf;
			ib_mad_complete_send_wr(mad_send_wr, &mad_send_wc);
		}
	} else {
		mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent,
						   mad_recv_wc);
		deref_mad_agent(mad_agent_priv);
	}
}
