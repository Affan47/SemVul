check_replay(struct network *n, struct ieee80211_frame *wh, int len)
{
	if (_state.s_state != STATE_ATTACK
	    || _state.s_curnet != n
	    || n->n_astate != ASTATE_WEP_FLOOD)
		return;

	if (!(wh->i_fc[1] |= IEEE80211_FC1_DIR_FROMDS))
		return;

	if (memcmp(wh->i_addr3, _state.s_mac, sizeof(wh->i_addr3)) != 0)
		return;

	if (len != (int) (n->n_replay_len - sizeof(*wh)))
		return;

	n->n_replay_got++;
	memcpy(&n->n_replay_last, &_state.s_now, sizeof(n->n_replay_last));


	do_flood(n);
}
