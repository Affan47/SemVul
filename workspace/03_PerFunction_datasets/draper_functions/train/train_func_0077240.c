qla83xx_idc_lock(scsi_qla_host_t *base_vha, uint16_t requester_id)
{
	uint16_t options = (requester_id << 15) | BIT_6;
	uint32_t data;
	uint32_t lock_owner;
	struct qla_hw_data *ha = base_vha->hw;


retry_lock:
	if (qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCK, &data)
	    == QLA_SUCCESS) {
		if (data) {

			qla83xx_wr_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    ha->portnum);
		} else {
			qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    &lock_owner);
			ql_dbg(ql_dbg_p3p, base_vha, 0xb063,
			    "Failed to acquire IDC lock, acquired by %d, "
			    "retrying...\n", lock_owner);


			if (qla83xx_idc_lock_recovery(base_vha)
			    == QLA_SUCCESS) {
				qla83xx_wait_logic();
				goto retry_lock;
			} else
				ql_log(ql_log_warn, base_vha, 0xb075,
				    "IDC Lock recovery FAILED.\n");
		}

	}

	return;


retry_lock2:
	if (qla83xx_access_control(base_vha, options, 0, 0, NULL)) {
		ql_dbg(ql_dbg_p3p, base_vha, 0xb072,
		    "Failed to acquire IDC lock. retrying...\n");

		if (qla83xx_idc_lock_recovery(base_vha) == QLA_SUCCESS) {
			qla83xx_wait_logic();
			goto retry_lock2;
		} else
			ql_log(ql_log_warn, base_vha, 0xb076,
			    "IDC Lock recovery FAILED.\n");
	}

	return;
}
