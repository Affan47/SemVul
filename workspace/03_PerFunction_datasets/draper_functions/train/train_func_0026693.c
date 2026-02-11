ocrdma_mbx_dealloc_pd_range(struct ocrdma_dev *dev)
{
	struct ocrdma_dealloc_pd_range *cmd;


	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD_RANGE, sizeof(*cmd));
	if (!cmd)
		goto mbx_err;

	if (dev->pd_mgr->max_normal_pd) {
		cmd->start_pd_id = dev->pd_mgr->pd_norm_start;
		cmd->pd_count = dev->pd_mgr->max_normal_pd;
		ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	}

	if (dev->pd_mgr->max_dpp_pd) {
		kfree(cmd);

		cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD_RANGE,
					  sizeof(*cmd));
		if (!cmd)
			goto mbx_err;

		cmd->start_pd_id = dev->pd_mgr->pd_dpp_start;
		cmd->pd_count = dev->pd_mgr->max_dpp_pd;
		ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	}
mbx_err:
	kfree(cmd);
}
