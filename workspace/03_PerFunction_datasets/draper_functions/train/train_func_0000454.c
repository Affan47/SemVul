parse_config(const char *filename)
{
    char line[MAX_LINE], *p;
    FILE *f;
    struct match *list = NULL;
    struct match **ep = &list;
    struct match *m;

    if (!filename)
	filename = syslinux_config_file();

    f = fopen(filename, "r");
    if (!f)
	return list;

    while (fgets(line, sizeof line, f)) {
	p = skipspace(line);

	if (!looking_at(p, "#"))
	    continue;
	p = skipspace(p + 1);

	if (!looking_at(p, "dev"))
	    continue;
	p = skipspace(p + 3);

	m = malloc(sizeof(struct match));
	if (!m)
	    continue;

	memset(m, 0, sizeof *m);
	m->rid_max = 0xff;

	for (;;) {
	    p = skipspace(p);

	    if (looking_at(p, "did")) {
		p = get_did(p + 3, &m->did, &m->did_mask);
	    } else if (looking_at(p, "sid")) {
		p = get_did(p + 3, &m->sid, &m->sid_mask);
	    } else if (looking_at(p, "rid")) {
		p = get_rid_range(p + 3, &m->rid_min, &m->rid_max);
	    } else {
		char *e;

		e = strchr(p, '\n');
		if (*e)
		    *e = '\0';
		e = strchr(p, '\r');
		if (*e)
		    *e = '\0';

		m->filename = strdup(p);
		if (!m->filename)
		    m->did = -1;
		break;
	    }
	}

	dprintf("DEV DID %08x/%08x SID %08x/%08x RID %02x-%02x CMD %s\n",
		m->did, m->did_mask, m->sid, m->sid_mask,
		m->rid_min, m->rid_max, m->filename);

	*ep = m;
	ep = &m->next;
    }

    return list;
}
