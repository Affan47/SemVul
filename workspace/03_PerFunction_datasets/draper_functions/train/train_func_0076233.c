_set_gres_cnt(char *orig_config, char **new_config,
			  uint32_t new_cnt, char *gres_name,
			  char *gres_name_colon, int gres_name_colon_len)
{
	char *new_configured_res = NULL, *node_gres_config;
	char *last_tok = NULL, *tok;

	if (*new_config)
		node_gres_config = xstrdup(*new_config);
	else if (orig_config)
		node_gres_config = xstrdup(orig_config);
	else
		return;

	tok = strtok_r(node_gres_config, ",", &last_tok);
	while (tok) {
		if (new_configured_res)
			xstrcat(new_configured_res, ",");
		if (strcmp(tok, gres_name) &&
		    strncmp(tok, gres_name_colon, gres_name_colon_len)) {
			xstrcat(new_configured_res, tok);
		} else if ((new_cnt % (1024 * 1024 * 1024)) == 0) {
			new_cnt /= (1024 * 1024 * 1024);
			xstrfmtcat(new_configured_res, "%s:%uG",
				   gres_name, new_cnt);
		} else if ((new_cnt % (1024 * 1024)) == 0) {
			new_cnt /= (1024 * 1024);
			xstrfmtcat(new_configured_res, "%s:%uM",
				   gres_name, new_cnt);
		} else if ((new_cnt % 1024) == 0) {
			new_cnt /= 1024;
			xstrfmtcat(new_configured_res, "%s:%uK",
				   gres_name, new_cnt);
		} else {
			xstrfmtcat(new_configured_res, "%s:%u",
				   gres_name, new_cnt);
		}
		tok = strtok_r(NULL, ",", &last_tok);
	}
	xfree(node_gres_config);
	xfree(*new_config);
	*new_config = new_configured_res;
}
