create_cond_regex_rule(const char *file, int line,
				  struct proxy *px, int dir, int action, int flags,
				  const char *cmd, const char *reg, const char *repl,
				  const char **cond_start)
{
	regex_t *preg = NULL;
	const char *err;
	int err_code = 0;
	struct acl_cond *cond = NULL;

	if (px == &defproxy) {
		Alert("parsing [%s:%d] : '%s' not allowed in 'defaults' section.\n", file, line, cmd);
		err_code |= ERR_ALERT | ERR_FATAL;
		goto err;
	}

	if (*reg == 0) {
		Alert("parsing [%s:%d] : '%s' expects <regex> as an argument.\n", file, line, cmd);
		err_code |= ERR_ALERT | ERR_FATAL;
		goto err;
	}

	if (warnifnotcap(px, PR_CAP_RS, file, line, cmd, NULL))
		err_code |= ERR_WARN;

	if (cond_start &&
	    (strcmp(*cond_start, "if") == 0 || strcmp(*cond_start, "unless") == 0)) {
		if ((cond = build_acl_cond(file, line, px, cond_start)) == NULL) {
			Alert("parsing [%s:%d] : error detected while parsing a '%s' condition.\n",
			      file, line, cmd);
			err_code |= ERR_ALERT | ERR_FATAL;
			goto err;
		}
	}
	else if (cond_start && **cond_start) {
		Alert("parsing [%s:%d] : '%s' : Expecting nothing, 'if', or 'unless', got '%s'.\n",
		      file, line, cmd, *cond_start);
		err_code |= ERR_ALERT | ERR_FATAL;
		goto err;
	}

	if (dir == ACL_DIR_REQ)
		err_code |= warnif_cond_requires_resp(cond, file, line);
	else
		err_code |= warnif_cond_requires_req(cond, file, line);

	preg = calloc(1, sizeof(regex_t));
	if (!preg) {
		Alert("parsing [%s:%d] : '%s' : not enough memory to build regex.\n", file, line, cmd);
		err_code = ERR_ALERT | ERR_FATAL;
		goto err;
	}

	if (regcomp(preg, reg, REG_EXTENDED | flags) != 0) {
		Alert("parsing [%s:%d] : '%s' : bad regular expression '%s'.\n", file, line, cmd, reg);
		err_code = ERR_ALERT | ERR_FATAL;
		goto err;
	}

	err = chain_regex((dir == ACL_DIR_REQ) ? &px->req_exp : &px->rsp_exp,
			  preg, action, repl ? strdup(repl) : NULL, cond);
	if (repl && err) {
		Alert("parsing [%s:%d] : '%s' : invalid character or unterminated sequence in replacement string near '%c'.\n",
		      file, line, cmd, *err);
		err_code |= ERR_ALERT | ERR_FATAL;
		goto err;
	}

	if (dir == ACL_DIR_REQ && warnif_misplaced_reqxxx(px, file, line, cmd))
		err_code |= ERR_WARN;

	return err_code;
 err:
	free(preg);
	return err_code;
}
