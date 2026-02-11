iscsit_determine_counts_for_list(
	struct iscsi_cmd *cmd,
	struct iscsi_build_list *bl,
	u32 *seq_count,
	u32 *pdu_count)
{
	int check_immediate = 0;
	u32 burstlength = 0, offset = 0;
	u32 unsolicited_data_length = 0;
	u32 mdsl;
	struct iscsi_conn *conn = cmd->conn;

	if (cmd->se_cmd.data_direction == DMA_TO_DEVICE)
		mdsl = cmd->conn->conn_ops->MaxXmitDataSegmentLength;
	else
		mdsl = cmd->conn->conn_ops->MaxRecvDataSegmentLength;

	if ((bl->type == PDULIST_IMMEDIATE) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		check_immediate = 1;

	if ((bl->type == PDULIST_UNSOLICITED) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		unsolicited_data_length = min(cmd->se_cmd.data_length,
			conn->sess->sess_ops->FirstBurstLength);

	while (offset < cmd->se_cmd.data_length) {
		*pdu_count += 1;

		if (check_immediate) {
			check_immediate = 0;
			offset += bl->immediate_data_length;
			*seq_count += 1;
			if (unsolicited_data_length)
				unsolicited_data_length -=
					bl->immediate_data_length;
			continue;
		}
		if (unsolicited_data_length > 0) {
			if ((offset + mdsl) >= cmd->se_cmd.data_length) {
				unsolicited_data_length -=
					(cmd->se_cmd.data_length - offset);
				offset += (cmd->se_cmd.data_length - offset);
				continue;
			}
			if ((offset + mdsl)
					>= conn->sess->sess_ops->FirstBurstLength) {
				unsolicited_data_length -=
					(conn->sess->sess_ops->FirstBurstLength -
					offset);
				offset += (conn->sess->sess_ops->FirstBurstLength -
					offset);
				burstlength = 0;
				*seq_count += 1;
				continue;
			}

			offset += mdsl;
			unsolicited_data_length -= mdsl;
			continue;
		}
		if ((offset + mdsl) >= cmd->se_cmd.data_length) {
			offset += (cmd->se_cmd.data_length - offset);
			continue;
		}
		if ((burstlength + mdsl) >=
		     conn->sess->sess_ops->MaxBurstLength) {
			offset += (conn->sess->sess_ops->MaxBurstLength -
					burstlength);
			burstlength = 0;
			*seq_count += 1;
			continue;
		}

		burstlength += mdsl;
		offset += mdsl;
	}
}
