qla4_8xxx_process_fw_error(struct scsi_qla_host *ha)
{
	uint32_t halt_status;
	int halt_status_unrecoverable = 0;

	halt_status = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_HALT_STATUS1);

	if (is_qla8022(ha)) {
		ql4_printk(KERN_INFO, ha, "%s: disabling pause transmit on port 0 & 1.\n",
			   __func__);
		qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x98,
				CRB_NIU_XG_PAUSE_CTL_P0 |
				CRB_NIU_XG_PAUSE_CTL_P1);

		if (QLA82XX_FWERROR_CODE(halt_status) == 0x67)
			ql4_printk(KERN_ERR, ha, "%s: Firmware aborted with error code 0x00006700. Device is being reset\n",
				   __func__);
		if (halt_status & HALT_STATUS_UNRECOVERABLE)
			halt_status_unrecoverable = 1;
	} else if (is_qla8032(ha) || is_qla8042(ha)) {
		if (halt_status & QLA83XX_HALT_STATUS_FW_RESET)
			ql4_printk(KERN_ERR, ha, "%s: Firmware error detected device is being reset\n",
				   __func__);
		else if (halt_status & QLA83XX_HALT_STATUS_UNRECOVERABLE)
			halt_status_unrecoverable = 1;
	}


	if (halt_status_unrecoverable) {
		set_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags);
	} else {
		ql4_printk(KERN_INFO, ha, "%s: detect abort needed!\n",
			   __func__);
		set_bit(DPC_RESET_HA, &ha->dpc_flags);
	}
	qla4xxx_mailbox_premature_completion(ha);
	qla4xxx_wake_dpc(ha);
}
