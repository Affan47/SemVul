vi_counter_incr_matchtable(struct hashtable *ht, char *s, char **t)
{
	while(*t) {
		int res;
		if ((*t)[0] == '\0' || strstr(s, *t) != NULL) {
			char *key = *(t+1) ? *(t+1) : *t;
			res = vi_counter_incr(ht, key);
			if (res == 0) return 1;
			return 0;
		}
		t += 2;
	}
	return 0;
}
