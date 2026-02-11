target_get_sess_cmd(struct se_cmd *se_cmd, bool ack_kref)
{
	struct se_session *se_sess = se_cmd->se_sess;
	unsigned long flags;
	int ret = 0;


	if (ack_kref) {
		kref_get(&se_cmd->cmd_kref);
		se_cmd->se_cmd_flags |= SCF_ACK_KREF;
	}

	spin_lock_irqsave(&se_sess->sess_cmd_lock, flags);
	if (se_sess->sess_tearing_down) {
		ret = -ESHUTDOWN;
		goto out;
	}
	se_cmd->transport_state |= CMD_T_PRE_EXECUTE;
	list_add_tail(&se_cmd->se_cmd_list, &se_sess->sess_cmd_list);
out:
	spin_unlock_irqrestore(&se_sess->sess_cmd_lock, flags);

	if (ret && ack_kref)
		target_put_sess_cmd(se_cmd);

	return ret;
}
