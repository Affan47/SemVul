ocrdma_set_create_qp_dpp_cmd(struct ocrdma_create_qp_req *cmd,
					 struct ocrdma_pd *pd,
					 struct ocrdma_qp *qp,
					 u8 enable_dpp_cq, u16 dpp_cq_id)
{
	pd->num_dpp_qp--;
	qp->dpp_enabled = true;
	cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK;
	if (!enable_dpp_cq)
		return;
	cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK;
	cmd->dpp_credits_cqid = dpp_cq_id;
	cmd->dpp_credits_cqid |= OCRDMA_CREATE_QP_REQ_DPP_CREDIT_LIMIT <<
					OCRDMA_CREATE_QP_REQ_DPP_CREDIT_SHIFT;
}
