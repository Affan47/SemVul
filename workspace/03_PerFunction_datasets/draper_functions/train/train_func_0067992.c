ipr_ioafp_query_ioa_cfg(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	struct ipr_inquiry_page3 *ucode_vpd = &ioa_cfg->vpd_cbs->page3_data;
	struct ipr_inquiry_cap *cap = &ioa_cfg->vpd_cbs->cap;

	ENTER;
	if (cap->cap & IPR_CAP_DUAL_IOA_RAID)
		ioa_cfg->dual_raid = 1;
	dev_info(&ioa_cfg->pdev->dev, "Adapter firmware version: %02X%02X%02X%02X\n",
		 ucode_vpd->major_release, ucode_vpd->card_type,
		 ucode_vpd->minor_release[0], ucode_vpd->minor_release[1]);
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
	ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

	ioarcb->cmd_pkt.cdb[0] = IPR_QUERY_IOA_CONFIG;
	ioarcb->cmd_pkt.cdb[6] = (ioa_cfg->cfg_table_size >> 16) & 0xff;
	ioarcb->cmd_pkt.cdb[7] = (ioa_cfg->cfg_table_size >> 8) & 0xff;
	ioarcb->cmd_pkt.cdb[8] = ioa_cfg->cfg_table_size & 0xff;

	ipr_init_ioadl(ipr_cmd, ioa_cfg->cfg_table_dma, ioa_cfg->cfg_table_size,
		       IPR_IOADL_FLAGS_READ_LAST);

	ipr_cmd->job_step = ipr_init_res_table;

	ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	return IPR_RC_JOB_RETURN;
}
