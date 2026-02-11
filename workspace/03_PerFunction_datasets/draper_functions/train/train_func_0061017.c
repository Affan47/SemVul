load_raw_table(FILE *fp)
{
	char buf[4096];
	struct ifstat_ent *db = NULL;
	struct ifstat_ent *n;

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		char *p;
		char *next;
		int i;

		if (buf[0] == '#') {
			buf[strlen(buf)-1] = 0;
			if (info_source[0] && strcmp(info_source, buf+1))
				source_mismatch = 1;
			strncpy(info_source, buf+1, sizeof(info_source)-1);
			continue;
		}
		if ((n = malloc(sizeof(*n))) == NULL)
			abort();

		if (!(p = strchr(buf, ' ')))
			abort();
		*p++ = 0;

		if (sscanf(buf, "%d", &n->ifindex) != 1)
			abort();
		if (!(next = strchr(p, ' ')))
			abort();
		*next++ = 0;

		n->name = strdup(p);
		p = next;

		for (i=0; i<MAXS; i++) {
			unsigned rate;
			if (!(next = strchr(p, ' ')))
				abort();
			*next++ = 0;
			if (sscanf(p, "%llu", n->val+i) != 1)
				abort();
			n->ival[i] = (__u32)n->val[i];
			p = next;
			if (!(next = strchr(p, ' ')))
				abort();
			*next++ = 0;
			if (sscanf(p, "%u", &rate) != 1)
				abort();
			n->rate[i] = rate;
			p = next;
		}
		n->next = db;
		db = n;
	}

	while (db) {
		n = db;
		db = db->next;
		n->next = kern_db;
		kern_db = n;
	}
}
