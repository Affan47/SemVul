qlt_free_cmd(struct qla_tgt_cmd *cmd)
{
	struct qla_tgt_sess *sess = cmd->sess;

	ql_dbg(ql_dbg_tgt, cmd->vha, 0xe074,
	    "%s: se_cmd[%p] ox_id %04x\n",
	    __func__, &cmd->se_cmd,
	    be16_to_cpu(cmd->atio.u.isp24.fcp_hdr.ox_id));

	BUG_ON(cmd->cmd_in_wq);

	if (cmd->sg_mapped)
		qlt_unmap_sg(cmd->vha, cmd);

	if (!cmd->q_full)
		qlt_decr_num_pend_cmds(cmd->vha);

	BUG_ON(cmd->sg_mapped);
	cmd->jiffies_at_free = get_jiffies_64();
	if (unlikely(cmd->free_sg))
		kfree(cmd->sg);

	if (!sess || !sess->se_sess) {
		WARN_ON(1);
		return;
	}
	cmd->jiffies_at_free = get_jiffies_64();
	percpu_ida_free(&sess->se_sess->sess_tag_pool, cmd->se_cmd.map_tag);
}
