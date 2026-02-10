dump_kern_db(FILE *fp, int to_hist)
{
	struct nstat_ent *n, *h;
	const char *eol = "\n";

	h = hist_db;
	if (json_output)
		fprintf(fp, "{ \"%s\":{", info_source);
	else
		fprintf(fp, "#%s\n", info_source);

	for (n=kern_db; n; n=n->next) {
		unsigned long long val = n->val;
		if (!dump_zeros && !val && !n->rate)
			continue;
		if (!match(n->id)) {
			struct nstat_ent *h1;
			if (!to_hist)
				continue;
			for (h1 = h; h1; h1 = h1->next) {
				if (strcmp(h1->id, n->id) == 0) {
					val = h1->val;
					h = h1->next;
					break;
				}
			}
		}

		if (json_output) {
			fprintf(fp, "%s    \"%s\":%llu",
				eol, n->id, val);
			eol = ",\n";
		} else
			fprintf(fp, "%-32s%-16llu%6.1f\n", n->id, val, n->rate);
	}
	if (json_output)
		fprintf(fp, "\n} }\n");
}
