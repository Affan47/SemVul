iscsi_recv_async_msg(iscsi_conn_t *conn, struct iscsi_hdr *hdr)
{
	iscsi_session_t *session = conn->session;
	struct iscsi_async *async_hdr = (struct iscsi_async *)hdr;
	char *buf = conn->data;
	unsigned int senselen;
	struct scsi_sense_hdr sshdr;

	log_debug(3, "Read AEN %d\n", async_hdr->async_event);

	switch (async_hdr->async_event) {
	case ISCSI_ASYNC_MSG_SCSI_EVENT:
		senselen = (buf[0] << 8) | buf[1];
		buf += 2;

		if (!scsi_normalize_sense((uint8_t *)buf, senselen, &sshdr)) {
			log_error("Could not handle AEN %d. Invalid sense.",
				  async_hdr->async_event);
			break;
		}

		if (sshdr.asc == 0x3f && sshdr.ascq == 0x0e)
			session_scan_host(session, session->hostno, NULL);
		break;
	case ISCSI_ASYNC_MSG_REQUEST_LOGOUT:
		log_warning("Target requests logout within %u seconds for "
			   "connection\n", ntohs(async_hdr->param3));
		if (iscsi_send_logout(conn))
			log_error("Could not send logout in response to"
				 "logout request aen\n");
		break;
	case ISCSI_ASYNC_MSG_DROPPING_CONNECTION:
		log_warning("Target dropping connection %u, reconnect min %u "
			    "max %u\n", ntohs(async_hdr->param1),
			    ntohs(async_hdr->param2), ntohs(async_hdr->param3));
		session->def_time2wait =
			(uint32_t)ntohs(async_hdr->param2) & 0x0000FFFFFL;
		break;
	case ISCSI_ASYNC_MSG_DROPPING_ALL_CONNECTIONS:
		log_warning("Target dropping all connections, reconnect min %u "
			    "max %u\n", ntohs(async_hdr->param2),
			     ntohs(async_hdr->param3));
		session->def_time2wait =
			(uint32_t)ntohs(async_hdr->param2) & 0x0000FFFFFL;
		break;
	case ISCSI_ASYNC_MSG_PARAM_NEGOTIATION:
		log_warning("Received async event param negotiation, "
			    "dropping session\n");
		__conn_error_handle(session, conn);
		break;
	case ISCSI_ASYNC_MSG_VENDOR_SPECIFIC:
	default:
		log_warning("AEN not supported\n");
	}
}
