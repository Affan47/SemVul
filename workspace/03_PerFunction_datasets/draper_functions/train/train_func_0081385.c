iscsit_send_response(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	struct iscsi_scsi_rsp *hdr = (struct iscsi_scsi_rsp *)&cmd->pdu[0];
	struct kvec *iov;
	u32 padding = 0, tx_size = 0;
	int iov_count = 0;
	bool inc_stat_sn = (cmd->i_state == ISTATE_SEND_STATUS);

	iscsit_build_rsp_pdu(cmd, conn, inc_stat_sn, hdr);

	iov = &cmd->iov_misc[0];
	iov[iov_count].iov_base	= cmd->pdu;
	iov[iov_count++].iov_len = ISCSI_HDR_LEN;
	tx_size += ISCSI_HDR_LEN;


	if (cmd->se_cmd.sense_buffer &&
	   ((cmd->se_cmd.se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) ||
	    (cmd->se_cmd.se_cmd_flags & SCF_EMULATED_TASK_SENSE))) {
		put_unaligned_be16(cmd->se_cmd.scsi_sense_length, cmd->sense_buffer);
		cmd->se_cmd.scsi_sense_length += sizeof (__be16);

		padding		= -(cmd->se_cmd.scsi_sense_length) & 3;
		hton24(hdr->dlength, (u32)cmd->se_cmd.scsi_sense_length);
		iov[iov_count].iov_base	= cmd->sense_buffer;
		iov[iov_count++].iov_len =
				(cmd->se_cmd.scsi_sense_length + padding);
		tx_size += cmd->se_cmd.scsi_sense_length;

		if (padding) {
			memset(cmd->sense_buffer +
				cmd->se_cmd.scsi_sense_length, 0, padding);
			tx_size += padding;
			pr_debug("Adding %u bytes of padding to"
				" SENSE.\n", padding);
		}

		if (conn->conn_ops->DataDigest) {
			iscsit_do_crypto_hash_buf(&conn->conn_tx_hash,
				cmd->sense_buffer,
				(cmd->se_cmd.scsi_sense_length + padding),
				0, NULL, (u8 *)&cmd->data_crc);

			iov[iov_count].iov_base    = &cmd->data_crc;
			iov[iov_count++].iov_len     = ISCSI_CRC_LEN;
			tx_size += ISCSI_CRC_LEN;

			pr_debug("Attaching CRC32 DataDigest for"
				" SENSE, %u bytes CRC 0x%08x\n",
				(cmd->se_cmd.scsi_sense_length + padding),
				cmd->data_crc);
		}

		pr_debug("Attaching SENSE DATA: %u bytes to iSCSI"
				" Response PDU\n",
				cmd->se_cmd.scsi_sense_length);
	}

	if (conn->conn_ops->HeaderDigest) {
		u32 *header_digest = (u32 *)&cmd->pdu[ISCSI_HDR_LEN];

		iscsit_do_crypto_hash_buf(&conn->conn_tx_hash, cmd->pdu,
				ISCSI_HDR_LEN, 0, NULL, (u8 *)header_digest);

		iov[0].iov_len += ISCSI_CRC_LEN;
		tx_size += ISCSI_CRC_LEN;
		pr_debug("Attaching CRC32 HeaderDigest for Response"
				" PDU 0x%08x\n", *header_digest);
	}

	cmd->iov_misc_count = iov_count;
	cmd->tx_size = tx_size;

	return 0;
}
