ndmp_sxa_mover_connect (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
#ifndef NDMOS_OPTION_NO_DATA_AGENT
	struct ndm_data_agent *	da = &sess->data_acb;
#endif
	struct ndm_tape_agent *	ta = &sess->tape_acb;
	ndmp9_error		error;
	int			will_write;
	char			reason[100];

      NDMS_WITH(ndmp9_mover_connect)


	switch (request->mode) {
	default:		NDMADR_RAISE_ILLEGAL_ARGS("mover_mode");
	case NDMP9_MOVER_MODE_READ:
		will_write = 1;
		break;

	case NDMP9_MOVER_MODE_WRITE:
		will_write = 0;
		break;
	}

	switch (request->addr.addr_type) {
	default:		NDMADR_RAISE_ILLEGAL_ARGS("mover_addr_type");
	case NDMP9_ADDR_LOCAL:
#ifdef NDMOS_OPTION_NO_DATA_AGENT
		NDMADR_RAISE_ILLEGAL_ARGS("mover LOCAL w/o local DATA agent");
#endif
		break;

	case NDMP9_ADDR_TCP:
		break;
	}


	if (ta->mover_state.state != NDMP9_MOVER_STATE_IDLE)
		NDMADR_RAISE_ILLEGAL_STATE("mover_state !IDLE");
#ifndef NDMOS_OPTION_NO_DATA_AGENT
	if (request->addr.addr_type == NDMP9_ADDR_LOCAL) {
		ndmp9_data_get_state_reply *ds = &da->data_state;

		if (ds->state != NDMP9_DATA_STATE_LISTEN)
			NDMADR_RAISE_ILLEGAL_STATE("data_state !LISTEN");

		if (ds->data_connection_addr.addr_type != NDMP9_ADDR_LOCAL)
			NDMADR_RAISE_ILLEGAL_STATE("data_addr !LOCAL");
	} else {
		if (da->data_state.state != NDMP9_DATA_STATE_IDLE)
			NDMADR_RAISE_ILLEGAL_STATE("data_state !IDLE");
	}
#endif


	error = mover_can_proceed (sess, will_write);
	if (error != NDMP9_NO_ERR) NDMADR_RAISE(error, "!mover_can_proceed");


	error = ndmis_audit_tape_connect (sess, request->addr.addr_type, reason);
	if (error != NDMP9_NO_ERR) NDMADR_RAISE(error, reason);

	error = ndmis_tape_connect (sess, &request->addr, reason);
	if (error != NDMP9_NO_ERR) NDMADR_RAISE(error, reason);

	ta->mover_state.data_connection_addr = request->addr;


	error = ndmta_mover_connect (sess, request->mode);
	if (error != NDMP9_NO_ERR) {

		NDMADR_RAISE(error, "!mover_connect");
	}

	return 0;
      NDMS_ENDWITH
}
