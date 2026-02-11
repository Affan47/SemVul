qla83xx_nic_core_reset(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_p3p, vha, 0xb058,
	    "Entered  %s().\n", __func__);

	if (vha->device_flags & DFLG_DEV_FAILED) {
		ql_log(ql_log_warn, vha, 0xb059,
		    "Device in unrecoverable FAILED state.\n");
		return QLA_FUNCTION_FAILED;
	}

	qla83xx_idc_lock(vha, 0);

	if (qla83xx_check_driver_presence(vha) != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0xb05a,
		    "Function=0x%x has been removed from IDC participation.\n",
		    ha->portnum);
		rval = QLA_FUNCTION_FAILED;
		goto exit;
	}

	qla83xx_reset_ownership(vha);

	rval = qla83xx_initiating_reset(vha);


	if (rval == QLA_SUCCESS) {
		rval = qla83xx_idc_state_handler(vha);

		if (rval == QLA_SUCCESS)
			ha->flags.nic_core_hung = 0;
		__qla83xx_clear_drv_ack(vha);
	}

exit:
	qla83xx_idc_unlock(vha, 0);

	ql_dbg(ql_dbg_p3p, vha, 0xb05b, "Exiting %s.\n", __func__);

	return rval;
}
