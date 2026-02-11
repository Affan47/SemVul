cmd_update(const char* lp, nsupdate_params_t *params)
{
	DBG("%s: lp='%s'\n", __func__, lp);


	int bp = tok_find(lp, cmd_array);
	if (bp < 0) return bp;


	cmd_handle_f *h = cmd_handle;
	if (h[bp] != cmd_add && h[bp] != cmd_del) {
		ERR("unexpected token '%s' after 'update', allowed: '%s'\n",
		    lp, "{add|del|delete}");
		return KNOT_EPARSEFAIL;
	}

	return h[bp](tok_skipspace(lp + TOK_L(cmd_array[bp])), params);
}
