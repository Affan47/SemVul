qla82xx_check_cmdpeg_state(struct qla_hw_data *ha)
{
	u32 val = 0;
	int retries = 60;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	do {
		read_lock(&ha->hw_lock);
		val = qla82xx_rd_32(ha, CRB_CMDPEG_STATE);
		read_unlock(&ha->hw_lock);

		switch (val) {
		case PHAN_INITIALIZE_COMPLETE:
		case PHAN_INITIALIZE_ACK:
			return QLA_SUCCESS;
		case PHAN_INITIALIZE_FAILED:
			break;
		default:
			break;
		}
		ql_log(ql_log_info, vha, 0x00a8,
		    "CRB_CMDPEG_STATE: 0x%x and retries:0x%x.\n",
		    val, retries);

		msleep(500);

	} while (--retries);

	ql_log(ql_log_fatal, vha, 0x00a9,
	    "Cmd Peg initialization failed: 0x%x.\n", val);

	val = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_PEGTUNE_DONE);
	read_lock(&ha->hw_lock);
	qla82xx_wr_32(ha, CRB_CMDPEG_STATE, PHAN_INITIALIZE_FAILED);
	read_unlock(&ha->hw_lock);
	return QLA_FUNCTION_FAILED;
}
