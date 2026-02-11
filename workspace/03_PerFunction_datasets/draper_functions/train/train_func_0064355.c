qla8044_process_stop_seq(struct scsi_qla_host *vha)
{
	vha->reset_tmplt.seq_index = 0;
	qla8044_process_reset_template(vha, vha->reset_tmplt.stop_offset);
	if (vha->reset_tmplt.seq_end != 1)
		ql_log(ql_log_fatal, vha, 0xb099,
		    "%s: Abrupt STOP Sub-Sequence end.\n", __func__);
}
