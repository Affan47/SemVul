qla24xx_read_fcp_prio_cfg(scsi_qla_host_t *vha)
{
	int len, max_len;
	uint32_t fcp_prio_addr;
	struct qla_hw_data *ha = vha->hw;

	if (!ha->fcp_prio_cfg) {
		ha->fcp_prio_cfg = vmalloc(FCP_PRIO_CFG_SIZE);
		if (!ha->fcp_prio_cfg) {
			ql_log(ql_log_warn, vha, 0x00d5,
			    "Unable to allocate memory for fcp priorty data (%x).\n",
			    FCP_PRIO_CFG_SIZE);
			return QLA_FUNCTION_FAILED;
		}
	}
	memset(ha->fcp_prio_cfg, 0, FCP_PRIO_CFG_SIZE);

	fcp_prio_addr = ha->flt_region_fcp_prio;


	ha->isp_ops->read_optrom(vha, (uint8_t *)ha->fcp_prio_cfg,
			fcp_prio_addr << 2, FCP_PRIO_CFG_HDR_SIZE);

	if (!qla24xx_fcp_prio_cfg_valid(vha, ha->fcp_prio_cfg, 0))
		goto fail;


	fcp_prio_addr += (FCP_PRIO_CFG_HDR_SIZE >> 2);
	len = ha->fcp_prio_cfg->num_entries * FCP_PRIO_CFG_ENTRY_SIZE;
	max_len = FCP_PRIO_CFG_SIZE - FCP_PRIO_CFG_HDR_SIZE;

	ha->isp_ops->read_optrom(vha, (uint8_t *)&ha->fcp_prio_cfg->entry[0],
			fcp_prio_addr << 2, (len < max_len ? len : max_len));


	if (!qla24xx_fcp_prio_cfg_valid(vha, ha->fcp_prio_cfg, 1))
		goto fail;

	ha->flags.fcp_prio_enabled = 1;
	return QLA_SUCCESS;
fail:
	vfree(ha->fcp_prio_cfg);
	ha->fcp_prio_cfg = NULL;
	return QLA_FUNCTION_FAILED;
}
