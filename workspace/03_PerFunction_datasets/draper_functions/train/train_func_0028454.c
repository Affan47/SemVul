replay_check(void *a)
{
	struct network *n = a;

	if (_state.s_state != STATE_ATTACK
	    || _state.s_curnet != n
	    || n->n_astate != ASTATE_WEP_FLOOD)
		return;

	if (n->n_replay_got > 3)
		return;

	n->n_replay_len = 0;
	n->n_astate = ASTATE_WEP_PRGA_GET;
}
