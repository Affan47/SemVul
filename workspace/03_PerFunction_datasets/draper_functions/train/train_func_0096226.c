qla8044_watchdog(struct scsi_qla_host *vha)
{
	uint32_t dev_state, halt_status;
	int halt_status_unrecoverable = 0;
	struct qla_hw_data *ha = vha->hw;


	if (!(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
	    test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags))) {
		dev_state = qla8044_rd_direct(vha, QLA8044_CRB_DEV_STATE_INDEX);

		if (qla8044_check_fw_alive(vha)) {
			ha->flags.isp82xx_fw_hung = 1;
			ql_log(ql_log_warn, vha, 0xb10a,
			    "Firmware hung.\n");
			qla82xx_clear_pending_mbx(vha);
		}

		if (qla8044_check_temp(vha)) {
			set_bit(ISP_UNRECOVERABLE, &vha->dpc_flags);
			ha->flags.isp82xx_fw_hung = 1;
			qla2xxx_wake_dpc(vha);
		} else if (dev_state == QLA8XXX_DEV_NEED_RESET &&
			   !test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags)) {
			ql_log(ql_log_info, vha, 0xb0d6,
			    "%s: HW State: NEED RESET!\n",
			    __func__);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		} else if (dev_state == QLA8XXX_DEV_NEED_QUIESCENT &&
		    !test_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags)) {
			ql_log(ql_log_info, vha, 0xb0d7,
			    "%s: HW State: NEED QUIES detected!\n",
			    __func__);
			set_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		} else  {

			if (ha->flags.isp82xx_fw_hung) {
				halt_status = qla8044_rd_direct(vha,
					QLA8044_PEG_HALT_STATUS1_INDEX);
				if (halt_status &
				    QLA8044_HALT_STATUS_FW_RESET) {
					ql_log(ql_log_fatal, vha,
					    0xb0d8, "%s: Firmware "
					    "error detected device "
					    "is being reset\n",
					    __func__);
				} else if (halt_status &
					    QLA8044_HALT_STATUS_UNRECOVERABLE) {
						halt_status_unrecoverable = 1;
				}


				if (halt_status_unrecoverable) {
					set_bit(ISP_UNRECOVERABLE,
					    &vha->dpc_flags);
				} else {
					if (dev_state ==
					    QLA8XXX_DEV_QUIESCENT) {
						set_bit(FCOE_CTX_RESET_NEEDED,
						    &vha->dpc_flags);
						ql_log(ql_log_info, vha, 0xb0d9,
						    "%s: FW CONTEXT Reset "
						    "needed!\n", __func__);
					} else {
						ql_log(ql_log_info, vha,
						    0xb0da, "%s: "
						    "detect abort needed\n",
						    __func__);
						set_bit(ISP_ABORT_NEEDED,
						    &vha->dpc_flags);
					}
				}
				qla2xxx_wake_dpc(vha);
			}
		}

	}
}
