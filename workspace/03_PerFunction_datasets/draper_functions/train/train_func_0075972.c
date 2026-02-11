parse_port(char *line, Node * node, int type, int maxports)
{
	char remotenodeid[NODEIDLEN], *sp;
	int portnum, isalias = 0;
	Port *port;
	char *s;

	if (line[0] == '@') {
		isalias = 1;
		line++;
	}

	portnum = atoi(line + 1);

	if (portnum < 0 || portnum > maxports) {
		IBWARN("bad port num %d: <%s>", portnum, line);
		return -1;
	}
	if (!portnum && line[1] != 0) {
		IBWARN("bad port: <%s>", line);
		return -1;
	}

	port = node_get_port(node, portnum);

	if (type != SWITCH_NODE && !portnum) {
		IBWARN("Port0 in non switch node <%s>", line);
		return -1;
	}

	if (!(s = parse_node_id(line, NULL))) {
		IBWARN("invalid remote nodeid: <%s>", line);
		return -1;
	}

	if (isalias) {
		if (new_alias(s, node, portnum) < 0)
			return -1;
		build_alias(port->alias, s, 1);
		s += strlen(s) + 1;
		goto parse_opt;
	}

	if (strchr(s, '@'))
		build_alias(port->remotealias, s, 0);

	expand_name(s, remotenodeid, &sp);
	PDEBUG("remotenodeid %s s %s sp %s", remotenodeid, s, sp);

	s += strlen(s) + 1;
	if (!sp && *s == '[')
		sp = s + 1;

	strncpy(port->remotenodeid, remotenodeid,
		sizeof(port->remotenodeid) - 1);
	if (!sp) {
		port->remoteport = 1;
		goto parse_opt;
	}
	if ((port->remoteport = atoi(sp)) <= 0) {
		IBWARN("invalid remote portnum %d: <%s>", port->remoteport, sp);
		port->remoteport = 0;
		return -1;
	}
      parse_opt:
	line = s;
	while (s && (s = strchr(s + 1, '='))) {
		char *opt = s;
		while (opt && !isalpha(*opt))
			opt--;
		if (!opt || parse_port_opt(port, opt, s + 1) < 0) {
			IBWARN("bad port option");
			return -1;
		}
		line = s + 1;
	}
	if (type != SWITCH_NODE && line && parse_port_lid_and_lmc(port, line) < 0) {
		IBWARN("cannot parse lid, lmc");
		return -1;
	}
	return 1;
}
