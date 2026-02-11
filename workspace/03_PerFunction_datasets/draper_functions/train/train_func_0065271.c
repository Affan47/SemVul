do_change_baselid(FILE * f, char *line)
{
	Port *port;
	Node *node;
	char *s = line;
	char *nodeid = 0, name[NAMELEN], *sp, *orig = 0;
	int portnum = -1;
	int lid = 0, lmc = -1;

	if (strsep(&s, "\""))
		orig = strsep(&s, "\"");

	if (!s) {
		fprintf(f, "# change baselid: bad parameter in \"%s\"\n", line);
		return -1;
	}

	nodeid = expand_name(orig, name, &sp);
	if (!sp && *s == '[')
		sp = s + 1;

	if (!(node = find_node(nodeid))) {
		fprintf(f, "# nodeid \"%s\" (%s) not found\n", orig, nodeid);
		return -1;
	}

	if (!sp) {
		fprintf(f, "# change baselid: missing portnum");
		return -1;
	}

	portnum = strtoul(sp, &sp, 0);
	if ((portnum < 1 && node->type != SWITCH_NODE)
	    || portnum > node->numports) {
		fprintf(f,
			"# can't change baselid for port %d at nodeid \"%s\"\n",
			portnum, nodeid);
		return -1;
	}

	if (node->type != SWITCH_NODE)
		portnum--;

	port = ports + node->portsbase + portnum;

	if (!sp || *sp != ']') {
		fprintf(f, "# change baselid: missing ']'\n");
		return -1;
	}

	sp++;

	if (sp && *sp)
		while (isspace(*sp))
			sp++;
	lid = strtoul(sp, &sp, 0);

	if (!lid) {
		fprintf(f, "# change baselid: bad lid\n");
		return -1;
	}

	if (sp && *sp)
		while (isspace(*sp))
			sp++;

	if (sp && *sp)
		lmc = strtoul(sp, 0, 0);

	port_change_lid(port, lid, lmc);
	return 1;
}
