player_inc_timed(struct player *p, int idx, int v, bool notify, bool check)
{
	timed_effect *effect;


	effect = &effects[idx];


	if ((idx < 0) || (idx > TMD_MAX)) return FALSE;


	if (check) {
		wieldeds_notice_flag(p, effect->resist);
		if (check_state(p, effect->resist, p->state.flags)) return FALSE;
	}


	if (idx == TMD_PARALYZED && p->timed[TMD_PARALYZED] > 0)
		return FALSE;


	v = v + p->timed[idx];

	return player_set_timed(p, idx, v, notify);
}
