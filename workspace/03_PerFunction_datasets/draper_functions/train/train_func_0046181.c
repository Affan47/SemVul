process_diff(xdfenv_t *xe, xdchange_t *xscr, xdemitcb_t *ecb,
			xdemitconf_t const *xecfg)
{
	long s1, s2, same, p_next, t_next;
	xdchange_t *xch, *xche;
	struct xdiff_emit_hunk_state *state = ecb->priv;
	xdiff_emit_hunk_consume_fn fn = state->consume;
	void *consume_callback_data = state->consume_callback_data;

	for (xch = xscr; xch; xch = xche->next) {
		xche = xdl_get_hunk(xch, xecfg);

		s1 = XDL_MAX(xch->i1 - xecfg->ctxlen, 0);
		s2 = XDL_MAX(xch->i2 - xecfg->ctxlen, 0);
		same = s2 + XDL_MAX(xch->i1 - s1, 0);
		p_next = xche->i1 + xche->chg1;
		t_next = xche->i2 + xche->chg2;

		fn(consume_callback_data, same, p_next, t_next);
	}
	return 0;
}
