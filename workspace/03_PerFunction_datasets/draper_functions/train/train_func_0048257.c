index_name_pos(struct index_state *istate, const char *name, int namelen)
{
	int first, last;

	first = 0;
	last = istate->cache_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		struct cache_entry *ce = istate->cache[next];
		int cmp = cache_name_compare(name, namelen, ce->name, ntohs(ce->ce_flags));
		if (!cmp)
			return next;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}
	return -first-1;
}
