ocrdma_mbx_query_qp(struct ocrdma_dev *dev, struct ocrdma_qp *qp,
			struct ocrdma_qp_params *param)
{
	int status = -ENOMEM;
	struct ocrdma_query_qp *cmd;
	struct ocrdma_query_qp_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_QP, sizeof(*rsp));
	if (!cmd)
		return status;
	cmd->qp_id = qp->id;
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_query_qp_rsp *)cmd;
	memcpy(param, &rsp->params, sizeof(struct ocrdma_qp_params));
mbx_err:
	kfree(cmd);
	return status;
}
