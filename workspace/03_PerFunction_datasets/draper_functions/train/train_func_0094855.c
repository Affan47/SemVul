nsupdate_process_line(char *lp, int len, void *arg)
{
	nsupdate_params_t *params = (nsupdate_params_t *)arg;


	for (int i = len - 1; i >= 0; i--) {
		if (isspace((unsigned char)lp[i]) == 0) {
			break;
		}
		lp[i] = '\0';
	}


	if (lp[0] == '\0' || lp[0] == ';') {
		return KNOT_EOK;
	}

	int ret = tok_find(lp, cmd_array);
	if (ret < 0) {
		return KNOT_EOK;
	}

	const char *cmd = cmd_array[ret];
	const char *val = tok_skipspace(lp + TOK_L(cmd));
	ret = cmd_handle[ret](val, params);
	if (ret != KNOT_EOK) {
		DBG("operation '%s' failed (%s)\n",
		    TOK_S(cmd), knot_strerror(ret));
	}

	return KNOT_EOK;
}
