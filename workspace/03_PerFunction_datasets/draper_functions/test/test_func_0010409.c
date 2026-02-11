qlcnic_83xx_enqueue_mbx_cmd(struct qlcnic_adapter *adapter,
				       struct qlcnic_cmd_args *cmd,
				       unsigned long *timeout)
{
	struct qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	if (test_bit(QLC_83XX_MBX_READY, &mbx->status)) {
		atomic_set(&cmd->rsp_status, QLC_83XX_MBX_RESPONSE_WAIT);
		init_completion(&cmd->completion);
		cmd->rsp_opcode = QLC_83XX_MBX_RESPONSE_UNKNOWN;

		spin_lock(&mbx->queue_lock);

		list_add_tail(&cmd->list, &mbx->cmd_q);
		mbx->num_cmds++;
		cmd->total_cmds = mbx->num_cmds;
		*timeout = cmd->total_cmds * QLC_83XX_MBX_TIMEOUT;
		queue_work(mbx->work_q, &mbx->work);

		spin_unlock(&mbx->queue_lock);

		return 0;
	}

	return -EBUSY;
}
