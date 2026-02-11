ndmis_audit_ep_connect (
  struct ndm_session *sess,
  ndmp9_addr_type addr_type,
  char *reason,
  struct ndmis_end_point *mine_ep,
  struct ndmis_end_point *peer_ep)
{
	ndmp9_error		error = NDMP9_NO_ERR;
	char *			reason_end;

	sprintf (reason, "IS %s_CONNECT: ", mine_ep->name);
	reason_end = reason;
	while (*reason_end) reason_end++;

	if (mine_ep->connect_status != NDMIS_CONN_IDLE) {
		sprintf (reason_end, "%s not idle", mine_ep->name);
		error = NDMP9_ILLEGAL_STATE_ERR;
		goto out;
	}

	switch (addr_type) {
	case NDMP9_ADDR_LOCAL:
		if (peer_ep->connect_status != NDMIS_CONN_LISTEN) {
			sprintf (reason_end, "LOCAL %s not LISTEN",
					peer_ep->name);
			error = NDMP9_ILLEGAL_STATE_ERR;
			goto out;
		}
		if (peer_ep->addr_type != NDMP9_ADDR_LOCAL) {
			sprintf (reason_end, "LOCAL %s not LOCAL",
					peer_ep->name);
			error = NDMP9_ILLEGAL_STATE_ERR;
			goto out;
		}
		break;

	case NDMP9_ADDR_TCP:
		if (peer_ep->connect_status != NDMIS_CONN_IDLE) {
			sprintf (reason_end, "LOCAL %s not IDLE",
					peer_ep->name);
			error = NDMP9_ILLEGAL_STATE_ERR;
			goto out;
		}
		break;

	default:
		strcpy (reason_end, "unknown addr_type");
		error = NDMP9_ILLEGAL_ARGS_ERR;
		goto out;
	}

  out:
	if (error == NDMP9_NO_ERR)
		strcpy (reason_end, "OK");

	return error;
}
