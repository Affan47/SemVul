plain_account_init(FILE *fp)
{
	char buf[BUFSIZE], *p, *q;
	u32 tid;
	int idx;

	tid = 0;
	while (fgets(buf, sizeof(buf), fp)) {
		q = buf;
		p = target_sep_string(&q);
		if (!p || *p == '#')
			continue;

		if (!strcasecmp(p, "Target")) {
			struct target *target;
			tid = 0;
			if (!(p = target_sep_string(&q)))
				continue;

			target = target_find_by_name(p);
			if (target)
				tid = target->tid;
		} else if (!((idx = param_index_by_name(p, user_keys)) < 0)) {
			char *name, *pass;
			name = target_sep_string(&q);
			pass = target_sep_string(&q);

			if (plain_account_add(tid, idx, name, pass) < 0)
				fprintf(stderr, "%s %s\n", name, pass);
		}
	}

	return;
}
