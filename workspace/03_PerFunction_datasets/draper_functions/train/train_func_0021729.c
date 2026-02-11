rqm_exec(struct ast_channel *chan, const char *data)
{
	int res=-1;
	char *parse, *temppos = NULL;
	struct member *mem = NULL;

	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(queuename);
		AST_APP_ARG(interface);
	);


	if (ast_strlen_zero(data)) {
		ast_log(LOG_WARNING, "RemoveQueueMember requires an argument (queuename[,interface])\n");
		return -1;
	}

	parse = ast_strdupa(data);

	AST_STANDARD_APP_ARGS(args, parse);

	if (ast_strlen_zero(args.interface)) {
		args.interface = ast_strdupa(ast_channel_name(chan));
		temppos = strrchr(args.interface, '-');
		if (temppos) {
			*temppos = '\0';
		}
	}

	ast_debug(1, "queue: %s, member: %s\n", args.queuename, args.interface);

	if (log_membername_as_agent) {
		mem = find_member_by_queuename_and_interface(args.queuename, args.interface);
	}

	switch (remove_from_queue(args.queuename, args.interface)) {
	case RES_OKAY:
		if (!mem || ast_strlen_zero(mem->membername)) {
			ast_queue_log(args.queuename, ast_channel_uniqueid(chan), args.interface, "REMOVEMEMBER", "%s", "");
		} else {
			ast_queue_log(args.queuename, ast_channel_uniqueid(chan), mem->membername, "REMOVEMEMBER", "%s", "");
		}
		ast_log(LOG_NOTICE, "Removed interface '%s' from queue '%s'\n", args.interface, args.queuename);
		pbx_builtin_setvar_helper(chan, "RQMSTATUS", "REMOVED");
		res = 0;
		break;
	case RES_EXISTS:
		ast_debug(1, "Unable to remove interface '%s' from queue '%s': Not there\n", args.interface, args.queuename);
		pbx_builtin_setvar_helper(chan, "RQMSTATUS", "NOTINQUEUE");
		res = 0;
		break;
	case RES_NOSUCHQUEUE:
		ast_log(LOG_WARNING, "Unable to remove interface from queue '%s': No such queue\n", args.queuename);
		pbx_builtin_setvar_helper(chan, "RQMSTATUS", "NOSUCHQUEUE");
		res = 0;
		break;
	case RES_NOT_DYNAMIC:
		ast_log(LOG_WARNING, "Unable to remove interface from queue '%s': '%s' is not a dynamic member\n", args.queuename, args.interface);
		pbx_builtin_setvar_helper(chan, "RQMSTATUS", "NOTDYNAMIC");
		res = 0;
		break;
	}

	if (mem) {
		ao2_ref(mem, -1);
	}

	return res;
}
