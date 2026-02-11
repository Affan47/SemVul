qlt_chk_qfull_thresh_hold(struct scsi_qla_host *vha,
	struct atio_from_isp *atio)
{
	struct qla_hw_data *ha = vha->hw;
	uint16_t status;

	if (ha->tgt.num_pend_cmds < Q_FULL_THRESH_HOLD(ha))
		return 0;

	status = temp_sam_status;
	qlt_send_busy(vha, atio, status);
	return 1;
}
