qla82xx_load_fw(scsi_qla_host_t *vha)
{
	int rst;
	struct fw_blob *blob;
	struct qla_hw_data *ha = vha->hw;

	if (qla82xx_pinit_from_rom(vha) != QLA_SUCCESS) {
		ql_log(ql_log_fatal, vha, 0x009f,
		    "Error during CRB initialization.\n");
		return QLA_FUNCTION_FAILED;
	}
	udelay(500);


	rst = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET);
	rst &= ~((1 << 28) | (1 << 24));
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, rst);


	if (ql2xfwloadbin == 2)
		goto try_blob_fw;

	ql_log(ql_log_info, vha, 0x00a0,
	    "Attempting to load firmware from flash.\n");

	if (qla82xx_fw_load_from_flash(ha) == QLA_SUCCESS) {
		ql_log(ql_log_info, vha, 0x00a1,
		    "Firmware loaded successfully from flash.\n");
		return QLA_SUCCESS;
	} else {
		ql_log(ql_log_warn, vha, 0x0108,
		    "Firmware load from flash failed.\n");
	}

try_blob_fw:
	ql_log(ql_log_info, vha, 0x00a2,
	    "Attempting to load firmware from blob.\n");


	blob = ha->hablob = qla2x00_request_firmware(vha);
	if (!blob) {
		ql_log(ql_log_fatal, vha, 0x00a3,
		    "Firmware image not present.\n");
		goto fw_load_failed;
	}


	if (qla82xx_validate_firmware_blob(vha,
		QLA82XX_FLASH_ROMIMAGE)) {

		if (qla82xx_validate_firmware_blob(vha,
			QLA82XX_UNIFIED_ROMIMAGE)) {
			ql_log(ql_log_fatal, vha, 0x00a4,
			    "No valid firmware image found.\n");
			return QLA_FUNCTION_FAILED;
		}
	}

	if (qla82xx_fw_load_from_blob(ha) == QLA_SUCCESS) {
		ql_log(ql_log_info, vha, 0x00a5,
		    "Firmware loaded successfully from binary blob.\n");
		return QLA_SUCCESS;
	}

	ql_log(ql_log_fatal, vha, 0x00a6,
	       "Firmware load failed for binary blob.\n");
	blob->fw = NULL;
	blob = NULL;

fw_load_failed:
	return QLA_FUNCTION_FAILED;
}
