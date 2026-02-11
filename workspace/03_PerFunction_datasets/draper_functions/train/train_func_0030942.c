handle_ib_smi(const struct ib_mad_port_private *port_priv,
				     const struct ib_mad_qp_info *qp_info,
				     const struct ib_wc *wc,
				     int port_num,
				     struct ib_mad_private *recv,
				     struct ib_mad_private *response)
{
	enum smi_forward_action retsmi;
	struct ib_smp *smp = (struct ib_smp *)recv->mad;

	if (smi_handle_dr_smp_recv(smp,
				   rdma_cap_ib_switch(port_priv->device),
				   port_num,
				   port_priv->device->phys_port_cnt) ==
				   IB_SMI_DISCARD)
		return IB_SMI_DISCARD;

	retsmi = smi_check_forward_dr_smp(smp);
	if (retsmi == IB_SMI_LOCAL)
		return IB_SMI_HANDLE;

	if (retsmi == IB_SMI_SEND) {
		if (smi_handle_dr_smp_send(smp,
					   rdma_cap_ib_switch(port_priv->device),
					   port_num) == IB_SMI_DISCARD)
			return IB_SMI_DISCARD;

		if (smi_check_local_smp(smp, port_priv->device) == IB_SMI_DISCARD)
			return IB_SMI_DISCARD;
	} else if (rdma_cap_ib_switch(port_priv->device)) {

		memcpy(response, recv, mad_priv_size(response));
		response->header.recv_wc.wc = &response->header.wc;
		response->header.recv_wc.recv_buf.mad = (struct ib_mad *)response->mad;
		response->header.recv_wc.recv_buf.grh = &response->grh;

		agent_send_response((const struct ib_mad_hdr *)response->mad,
				    &response->grh, wc,
				    port_priv->device,
				    smi_get_fwd_port(smp),
				    qp_info->qp->qp_num,
				    response->mad_size,
				    false);

		return IB_SMI_DISCARD;
	}
	return IB_SMI_HANDLE;
}
