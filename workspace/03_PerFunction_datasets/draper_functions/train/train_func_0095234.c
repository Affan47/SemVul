tcp_parse_response_rule(char **args, int arg, int section_type,
                                   struct proxy *curpx, struct proxy *defpx,
                                   struct tcp_rule *rule, char **err,
                                   unsigned int where,
                                   const char *file, int line)
{
	if (curpx == defpx || !(curpx->cap & PR_CAP_BE)) {
		memprintf(err, "%s %s is only allowed in 'backend' sections",
		          args[0], args[1]);
		return -1;
	}

	if (strcmp(args[arg], "accept") == 0) {
		arg++;
		rule->action = TCP_ACT_ACCEPT;
	}
	else if (strcmp(args[arg], "reject") == 0) {
		arg++;
		rule->action = TCP_ACT_REJECT;
	}
	else if (strcmp(args[arg], "close") == 0) {
		arg++;
		rule->action = TCP_ACT_CLOSE;
	}
	else {
		memprintf(err,
		          "'%s %s' expects 'accept', 'close' or 'reject' in %s '%s' (got '%s')",
		          args[0], args[1], proxy_type_str(curpx), curpx->id, args[arg]);
		return -1;
	}

	if (strcmp(args[arg], "if") == 0 || strcmp(args[arg], "unless") == 0) {
		if ((rule->cond = build_acl_cond(file, line, curpx, (const char **)args+arg, err)) == NULL) {
			memprintf(err,
			          "'%s %s %s' : error detected in %s '%s' while parsing '%s' condition : %s",
			          args[0], args[1], args[2], proxy_type_str(curpx), curpx->id, args[arg], *err);
			return -1;
		}
	}
	else if (*args[arg]) {
		memprintf(err,
			 "'%s %s %s' only accepts 'if' or 'unless', in %s '%s' (got '%s')",
			 args[0], args[1], args[2], proxy_type_str(curpx), curpx->id, args[arg]);
		return -1;
	}
	return 0;
}
