qla8044_flash_write_u32(struct scsi_qla_host *vha, uint32_t addr,
			uint32_t *p_data)
{
	int ret_val = QLA_SUCCESS;

	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_ADDR,
	    0x00800000 | (addr >> 2));
	if (ret_val) {
		ql_log(ql_log_warn, vha, 0xb134,
		    "%s: Failed write to FLASH_ADDR.\n", __func__);
		goto exit_func;
	}
	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_WRDATA, *p_data);
	if (ret_val) {
		ql_log(ql_log_warn, vha, 0xb135,
		    "%s: Failed write to FLASH_WRDATA.\n", __func__);
		goto exit_func;
	}
	ret_val = qla8044_wr_reg_indirect(vha, QLA8044_FLASH_CONTROL, 0x3D);
	if (ret_val) {
		ql_log(ql_log_warn, vha, 0xb136,
		    "%s: Failed write to FLASH_CONTROL.\n", __func__);
		goto exit_func;
	}
	ret_val = qla8044_poll_flash_status_reg(vha);
	if (ret_val) {
		ql_log(ql_log_warn, vha, 0xb137,
		    "%s: Poll flash status failed.\n", __func__);
	}

exit_func:
	return ret_val;
}
