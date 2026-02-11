ndmp_sxa_mover_abort (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
	struct ndm_tape_agent *	ta = &sess->tape_acb;

      NDMS_WITH_VOID_REQUEST(ndmp9_mover_abort)
	if (ta->mover_state.state != NDMP9_MOVER_STATE_LISTEN
	 && ta->mover_state.state != NDMP9_MOVER_STATE_ACTIVE
	 && ta->mover_state.state != NDMP9_MOVER_STATE_PAUSED) {
		NDMADR_RAISE_ILLEGAL_STATE("mover_state");
	}

	ndmta_mover_abort (sess);

	return 0;
      NDMS_ENDWITH
}
