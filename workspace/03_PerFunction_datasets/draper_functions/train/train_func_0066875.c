kallsyms_symbol_complete(char *prefix_name, int max_len)
{
	loff_t pos = 0;
	int prefix_len = strlen(prefix_name), prev_len = 0;
	int i, number = 0;
	const char *name;

	while ((name = kdb_walk_kallsyms(&pos))) {
		if (strncmp(name, prefix_name, prefix_len) == 0) {
			strcpy(ks_namebuf, name);

			if (++number == 1) {
				prev_len = min_t(int, max_len-1,
						 strlen(ks_namebuf));
				memcpy(ks_namebuf_prev, ks_namebuf, prev_len);
				ks_namebuf_prev[prev_len] = '\0';
				continue;
			}
			for (i = 0; i < prev_len; i++) {
				if (ks_namebuf[i] != ks_namebuf_prev[i]) {
					prev_len = i;
					ks_namebuf_prev[i] = '\0';
					break;
				}
			}
		}
	}
	if (prev_len > prefix_len)
		memcpy(prefix_name, ks_namebuf_prev, prev_len+1);
	return number;
}
