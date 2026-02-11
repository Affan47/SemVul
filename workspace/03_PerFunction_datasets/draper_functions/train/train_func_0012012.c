tcm_qla2xxx_handle_cmd(scsi_qla_host_t *vha, struct qla_tgt_cmd *cmd,
	unsigned char *cdb, uint32_t data_length, int fcp_task_attr,
	int data_dir, int bidi)
{
	struct se_cmd *se_cmd = &cmd->se_cmd;
	struct se_session *se_sess;
	struct qla_tgt_sess *sess;
	int flags = TARGET_SCF_ACK_KREF;

	if (bidi)
		flags |= TARGET_SCF_BIDI_OP;

	if (se_cmd->cpuid != WORK_CPU_UNBOUND)
		flags |= TARGET_SCF_USE_CPUID;

	sess = cmd->sess;
	if (!sess) {
		pr_err("Unable to locate struct qla_tgt_sess from qla_tgt_cmd\n");
		return -EINVAL;
	}

	se_sess = sess->se_sess;
	if (!se_sess) {
		pr_err("Unable to locate active struct se_session\n");
		return -EINVAL;
	}

	cmd->vha->tgt_counters.qla_core_sbt_cmd++;
	return target_submit_cmd(se_cmd, se_sess, cdb, &cmd->sense_buffer[0],
				cmd->unpacked_lun, data_length, fcp_task_attr,
				data_dir, flags);
}
