check_allowed(const struct ipset_type *type, enum ipset_cmd command)
{
	uint64_t flags = ipset_data_flags(ipset_session_data(session));
	enum ipset_adt cmd = cmd2cmd(command);
	uint64_t allowed = type->full[cmd];
	uint64_t cmdflags = command == IPSET_CMD_CREATE
				? IPSET_CREATE_FLAGS : IPSET_ADT_FLAGS;
	const struct ipset_arg *arg = type->args[cmd];
	enum ipset_opt i;


	if (allowed & IPSET_FLAG(IPSET_OPT_IP_TO))
		allowed |= IPSET_FLAG(IPSET_OPT_CIDR);

	for (i = IPSET_OPT_IP; i < IPSET_OPT_FLAGS; i++) {
		if (!(cmdflags & IPSET_FLAG(i)) ||
		    (allowed & IPSET_FLAG(i)) ||
		    !(flags & IPSET_FLAG(i)))
			continue;

		switch (i) {
		case IPSET_OPT_CIDR:
			exit_error(OTHER_PROBLEM,
				"IP/CIDR range is not allowed in command %s "
				"with set type %s and family %s",
				cmd2name(command), type->name,
				session_family());
			return;
		case IPSET_OPT_IP_TO:
			exit_error(OTHER_PROBLEM,
				"FROM-TO IP range is not allowed in command %s "
				"with set type %s and family %s",
				cmd2name(command), type->name,
				session_family());
			return;
		case IPSET_OPT_PORT_TO:
			exit_error(OTHER_PROBLEM,
				"FROM-TO port range is not allowed in command %s "
				"with set type %s and family %s",
				cmd2name(command), type->name,
				session_family());
			return;
		default:
			break;
		}

		if (!arg) {
			exit_error(OTHER_PROBLEM,
				"There are not allowed options (%u) "
				"but option list is NULL. "
				"It's a bug, please report the problem.", i);
			return;
		}
		for (; arg->opt; arg++) {
			if (arg->opt != i)
				continue;
			exit_error(OTHER_PROBLEM,
				"%s parameter is not allowed in command %s "
				"with set type %s and family %s",
				arg->name[0],
				cmd2name(command), type->name,
				session_family());
			return;
		}
		exit_error(OTHER_PROBLEM,
			"There are not allowed options (%u) "
			"but can't resolve them. "
			"It's a bug, please report the problem.", i);
		return;
	}
}
