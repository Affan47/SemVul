ocrdma_mbx_delete_q(struct ocrdma_dev *dev,
			       struct ocrdma_queue_info *q, int queue_type)
{
	u8 opcode = 0;
	int status;
	struct ocrdma_delete_q_req *cmd = dev->mbx_cmd;

	switch (queue_type) {
	case QTYPE_MCCQ:
		opcode = OCRDMA_CMD_DELETE_MQ;
		break;
	case QTYPE_CQ:
		opcode = OCRDMA_CMD_DELETE_CQ;
		break;
	case QTYPE_EQ:
		opcode = OCRDMA_CMD_DELETE_EQ;
		break;
	default:
		BUG();
	}
	memset(cmd, 0, sizeof(*cmd));
	ocrdma_init_mch(&cmd->req, opcode, OCRDMA_SUBSYS_COMMON, sizeof(*cmd));
	cmd->id = q->id;

	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, sizeof(*cmd), NULL, NULL);
	if (!status)
		q->created = false;
	return status;
}
