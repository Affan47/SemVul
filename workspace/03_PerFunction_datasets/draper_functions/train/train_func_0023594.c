iscsit_build_pdu_and_seq_lists(
	struct iscsi_cmd *cmd,
	u32 immediate_data_length)
{
	struct iscsi_build_list bl;
	u32 pdu_count = 0, seq_count = 1;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_pdu *pdu = NULL;
	struct iscsi_seq *seq = NULL;

	struct iscsi_session *sess = conn->sess;
	struct iscsi_node_attrib *na;


	if (sess->sess_ops->DataSequenceInOrder &&
	    sess->sess_ops->DataPDUInOrder)
		return 0;

	if (cmd->data_direction == DMA_NONE)
		return 0;

	na = iscsit_tpg_get_node_attrib(sess);
	memset(&bl, 0, sizeof(struct iscsi_build_list));

	if (cmd->data_direction == DMA_FROM_DEVICE) {
		bl.data_direction = ISCSI_PDU_READ;
		bl.type = PDULIST_NORMAL;
		if (na->random_datain_pdu_offsets)
			bl.randomize |= RANDOM_DATAIN_PDU_OFFSETS;
		if (na->random_datain_seq_offsets)
			bl.randomize |= RANDOM_DATAIN_SEQ_OFFSETS;
	} else {
		bl.data_direction = ISCSI_PDU_WRITE;
		bl.immediate_data_length = immediate_data_length;
		if (na->random_r2t_offsets)
			bl.randomize |= RANDOM_R2T_OFFSETS;

		if (!cmd->immediate_data && !cmd->unsolicited_data)
			bl.type = PDULIST_NORMAL;
		else if (cmd->immediate_data && !cmd->unsolicited_data)
			bl.type = PDULIST_IMMEDIATE;
		else if (!cmd->immediate_data && cmd->unsolicited_data)
			bl.type = PDULIST_UNSOLICITED;
		else if (cmd->immediate_data && cmd->unsolicited_data)
			bl.type = PDULIST_IMMEDIATE_AND_UNSOLICITED;
	}

	iscsit_determine_counts_for_list(cmd, &bl, &seq_count, &pdu_count);

	if (!conn->sess->sess_ops->DataSequenceInOrder) {
		seq = kcalloc(seq_count, sizeof(struct iscsi_seq), GFP_ATOMIC);
		if (!seq) {
			pr_err("Unable to allocate struct iscsi_seq list\n");
			return -ENOMEM;
		}
		cmd->seq_list = seq;
		cmd->seq_count = seq_count;
	}

	if (!conn->sess->sess_ops->DataPDUInOrder) {
		pdu = kcalloc(pdu_count, sizeof(struct iscsi_pdu), GFP_ATOMIC);
		if (!pdu) {
			pr_err("Unable to allocate struct iscsi_pdu list.\n");
			kfree(seq);
			return -ENOMEM;
		}
		cmd->pdu_list = pdu;
		cmd->pdu_count = pdu_count;
	}

	return iscsit_do_build_pdu_and_seq_lists(cmd, &bl);
}
