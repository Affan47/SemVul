ipr_ioafp_page3_inquiry(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;

	ipr_cmd->job_step = ipr_ioafp_cap_inquiry;

	ipr_ioafp_inquiry(ipr_cmd, 1, 3,
			  ioa_cfg->vpd_cbs_dma + offsetof(struct ipr_misc_cbs, page3_data),
			  sizeof(struct ipr_inquiry_page3));

	LEAVE;
	return IPR_RC_JOB_RETURN;
}
