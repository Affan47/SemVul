qla4_83xx_post_loopback_config(struct scsi_qla_host *ha,
					  uint32_t *mbox_cmd)
{
	int status = QLA_SUCCESS;
	uint32_t config = 0;

	DEBUG2(ql4_printk(KERN_INFO, ha, "%s: in\n", __func__));

	status = qla4_83xx_get_port_config(ha, &config);
	if (status != QLA_SUCCESS)
		goto exit_post_loopback_config;

	DEBUG2(ql4_printk(KERN_INFO, ha, "%s: port config=%08X\n", __func__,
			  config));

	if (mbox_cmd[1] == QL_DIAG_CMD_TEST_INT_LOOPBACK)
		config &= ~ENABLE_INTERNAL_LOOPBACK;
	else if (mbox_cmd[1] == QL_DIAG_CMD_TEST_EXT_LOOPBACK)
		config &= ~ENABLE_EXTERNAL_LOOPBACK;

	config |= ENABLE_DCBX;

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "%s: Restore default port config=%08X\n", __func__,
			  config));

	ha->notify_idc_comp = 1;
	if (ha->addl_fw_state & FW_ADDSTATE_LINK_UP)
		ha->notify_link_up_comp = 1;

	status = qla4_83xx_set_port_config(ha, &config);
	if (status != QLA_SUCCESS) {
		ql4_printk(KERN_INFO, ha, "%s: Scheduling adapter reset\n",
			   __func__);
		set_bit(DPC_RESET_HA, &ha->dpc_flags);
		clear_bit(AF_LOOPBACK, &ha->flags);
		goto exit_post_loopback_config;
	}

exit_post_loopback_config:
	DEBUG2(ql4_printk(KERN_INFO, ha, "%s: status = %s\n", __func__,
			  STATUS(status)));
	return status;
}
