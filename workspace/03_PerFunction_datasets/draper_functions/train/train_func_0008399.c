qla8044_start_firmware(struct scsi_qla_host *vha)
{
	int ret_val = QLA_SUCCESS;

	if (qla8044_restart(vha)) {
		ql_log(ql_log_fatal, vha, 0xb0ad,
		    "%s: Restart Error!!!, Need Reset!!!\n",
		    __func__);
		ret_val = QLA_FUNCTION_FAILED;
		goto exit_start_fw;
	} else
		ql_dbg(ql_dbg_p3p, vha, 0xb0af,
		    "%s: Restart done!\n", __func__);

	ret_val = qla8044_check_cmd_peg_status(vha);
	if (ret_val) {
		ql_log(ql_log_fatal, vha, 0xb0b0,
		    "%s: Peg not initialized!\n", __func__);
		ret_val = QLA_FUNCTION_FAILED;
	}

exit_start_fw:
	return ret_val;
}
