ocrdma_mbx_query_dev(struct ocrdma_dev *dev)
{
	int status = -ENOMEM;
	struct ocrdma_mbx_query_config *rsp;
	struct ocrdma_mqe *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_CONFIG, sizeof(*cmd));
	if (!cmd)
		return status;
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_mbx_query_config *)cmd;
	ocrdma_get_attr(dev, &dev->attr, rsp);
mbx_err:
	kfree(cmd);
	return status;
}
