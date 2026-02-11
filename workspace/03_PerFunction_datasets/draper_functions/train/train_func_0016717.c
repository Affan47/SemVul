iscsi_iser_recv(struct iscsi_conn *conn, struct iscsi_hdr *hdr,
		char *rx_data, int rx_data_len)
{
	int rc = 0;
	int datalen;


	datalen = ntoh24(hdr->dlength);
	if (datalen > rx_data_len || (datalen + 4) < rx_data_len) {
		iser_err("wrong datalen %d (hdr), %d (IB)\n",
			datalen, rx_data_len);
		rc = ISCSI_ERR_DATALEN;
		goto error;
	}

	if (datalen != rx_data_len)
		iser_dbg("aligned datalen (%d) hdr, %d (IB)\n",
			datalen, rx_data_len);

	rc = iscsi_complete_pdu(conn, hdr, rx_data, rx_data_len);
	if (rc && rc != ISCSI_ERR_NO_SCSI_CMD)
		goto error;

	return;
error:
	iscsi_conn_failure(conn, rc);
}
