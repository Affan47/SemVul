ndmta_mover_pending (struct ndm_session *sess,
  ndmp9_mover_state pending_state,
  ndmp9_mover_halt_reason halt_reason,
  ndmp9_mover_pause_reason pause_reason)
{
	struct ndm_tape_agent *	ta = &sess->tape_acb;

	if (ta->pending_change_after_drain) {

	}

	ta->pending_mover_state = pending_state;
	ta->pending_mover_halt_reason = halt_reason;
	ta->pending_mover_pause_reason = pause_reason;
	ta->pending_change_after_drain = 1;
}
