ipr_ioafp_pageC4_inquiry(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_inquiry_page0 *page0 = &ioa_cfg->vpd_cbs->page0_data;
	struct ipr_inquiry_pageC4 *pageC4 = &ioa_cfg->vpd_cbs->pageC4_data;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_set_caching_parameters;
	memset(pageC4, 0, sizeof(*pageC4));

	if (ipr_inquiry_page_supported(page0, 0xC4)) {
		ipr_ioafp_inquiry(ipr_cmd, 1, 0xC4,
				  (ioa_cfg->vpd_cbs_dma
				   + offsetof(struct ipr_misc_cbs,
					      pageC4_data)),
				  sizeof(struct ipr_inquiry_pageC4));
		return IPR_RC_JOB_RETURN;
	}

	LEAVE;
	return IPR_RC_JOB_CONTINUE;
}
