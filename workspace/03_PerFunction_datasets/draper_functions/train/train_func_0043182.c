ocrdma_mbx_alloc_pd_range(struct ocrdma_dev *dev)
{
	int status = -ENOMEM;
	size_t pd_bitmap_size;
	struct ocrdma_alloc_pd_range *cmd;
	struct ocrdma_alloc_pd_range_rsp *rsp;


	if (dev->attr.max_dpp_pds) {
		cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_PD_RANGE,
					  sizeof(*cmd));
		if (!cmd)
			return -ENOMEM;
		cmd->pd_count = dev->attr.max_dpp_pds;
		cmd->enable_dpp_rsvd |= OCRDMA_ALLOC_PD_ENABLE_DPP;
		status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
		rsp = (struct ocrdma_alloc_pd_range_rsp *)cmd;

		if (!status && (rsp->dpp_page_pdid & OCRDMA_ALLOC_PD_RSP_DPP) &&
		    rsp->pd_count) {
			dev->pd_mgr->dpp_page_index = rsp->dpp_page_pdid >>
					OCRDMA_ALLOC_PD_RSP_DPP_PAGE_SHIFT;
			dev->pd_mgr->pd_dpp_start = rsp->dpp_page_pdid &
					OCRDMA_ALLOC_PD_RNG_RSP_START_PDID_MASK;
			dev->pd_mgr->max_dpp_pd = rsp->pd_count;
			pd_bitmap_size =
				BITS_TO_LONGS(rsp->pd_count) * sizeof(long);
			dev->pd_mgr->pd_dpp_bitmap = kzalloc(pd_bitmap_size,
							     GFP_KERNEL);
		}
		kfree(cmd);
	}

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_PD_RANGE, sizeof(*cmd));
	if (!cmd)
		return -ENOMEM;

	cmd->pd_count = dev->attr.max_pd - dev->attr.max_dpp_pds;
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	rsp = (struct ocrdma_alloc_pd_range_rsp *)cmd;
	if (!status && rsp->pd_count) {
		dev->pd_mgr->pd_norm_start = rsp->dpp_page_pdid &
					OCRDMA_ALLOC_PD_RNG_RSP_START_PDID_MASK;
		dev->pd_mgr->max_normal_pd = rsp->pd_count;
		pd_bitmap_size = BITS_TO_LONGS(rsp->pd_count) * sizeof(long);
		dev->pd_mgr->pd_norm_bitmap = kzalloc(pd_bitmap_size,
						      GFP_KERNEL);
	}
	kfree(cmd);

	if (dev->pd_mgr->pd_norm_bitmap || dev->pd_mgr->pd_dpp_bitmap) {

		dev->pd_mgr->pd_prealloc_valid = true;
		return 0;
	}
	return status;
}
