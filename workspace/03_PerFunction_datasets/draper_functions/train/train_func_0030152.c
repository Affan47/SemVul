iscsit_create_recovery_datain_values_datasequenceinorder_yes(
	struct iscsi_cmd *cmd,
	struct iscsi_datain_req *dr)
{
	u32 data_sn = 0, data_sn_count = 0;
	u32 pdu_start = 0, seq_no = 0;
	u32 begrun = dr->begrun;
	struct iscsi_conn *conn = cmd->conn;

	while (begrun > data_sn++) {
		data_sn_count++;
		if ((dr->next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) {
			dr->read_data_done +=
				conn->conn_ops->MaxRecvDataSegmentLength;
			dr->next_burst_len +=
				conn->conn_ops->MaxRecvDataSegmentLength;
		} else {
			dr->read_data_done +=
				(conn->sess->sess_ops->MaxBurstLength -
				 dr->next_burst_len);
			dr->next_burst_len = 0;
			pdu_start += data_sn_count;
			data_sn_count = 0;
			seq_no++;
		}
	}

	if (!conn->sess->sess_ops->DataPDUInOrder) {
		cmd->seq_no = seq_no;
		cmd->pdu_start = pdu_start;
		cmd->pdu_send_order = data_sn_count;
	}

	return 0;
}
