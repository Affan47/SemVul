qla8044_set_win_base(scsi_qla_host_t *vha, uint32_t addr)
{
	uint32_t val;
	int ret_val = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;

	qla8044_wr_reg(ha, QLA8044_CRB_WIN_FUNC(ha->portnum), addr);
	val = qla8044_rd_reg(ha, QLA8044_CRB_WIN_FUNC(ha->portnum));

	if (val != addr) {
		ql_log(ql_log_warn, vha, 0xb087,
		    "%s: Failed to set register window : "
		    "addr written 0x%x, read 0x%x!\n",
		    __func__, addr, val);
		ret_val = QLA_FUNCTION_FAILED;
	}
	return ret_val;
}
