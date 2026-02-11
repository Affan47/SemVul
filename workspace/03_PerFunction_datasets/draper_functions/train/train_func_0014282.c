iscsit_handle_data_out(struct iscsi_conn *conn, unsigned char *buf)
{
	struct iscsi_cmd *cmd = NULL;
	struct iscsi_data *hdr = (struct iscsi_data *)buf;
	int rc;
	bool data_crc_failed = false;

	rc = iscsit_check_dataout_hdr(conn, buf, &cmd);
	if (rc < 0)
		return 0;
	else if (!cmd)
		return 0;

	rc = iscsit_get_dataout(conn, cmd, hdr);
	if (rc < 0)
		return rc;
	else if (rc > 0)
		data_crc_failed = true;

	return iscsit_check_dataout_payload(cmd, hdr, data_crc_failed);
}
