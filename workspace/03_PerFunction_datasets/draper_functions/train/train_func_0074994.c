data_can_connect_and_start (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn,
  ndmp9_addr *data_addr,
  ndmp9_mover_mode mover_mode)
{
	int			rc;


	switch (mover_mode) {
	default:		NDMADR_RAISE_ILLEGAL_ARGS("mover_mode");
	case NDMP9_MOVER_MODE_READ:
	case NDMP9_MOVER_MODE_WRITE:
		break;
	}

	rc = data_can_connect (sess, xa, ref_conn, data_addr);
	if (rc) return rc;

#ifndef NDMOS_OPTION_NO_TAPE_AGENT
	if (data_addr->addr_type == NDMP9_ADDR_LOCAL) {
		struct ndm_tape_agent *		ta = &sess->tape_acb;
		ndmp9_mover_get_state_reply *	ms = &ta->mover_state;

		if (ms->mode != mover_mode)
			NDMADR_RAISE_ILLEGAL_STATE("mover_mode mismatch");
	}
#endif

	return 0;
}
