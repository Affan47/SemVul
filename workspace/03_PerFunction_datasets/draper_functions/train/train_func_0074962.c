hostlist_find(hostlist_t hl, const char *hostname)
{
	int i, count, ret = -1;
	hostname_t hn;

	if (!hostname || !hl)
		return -1;

	hn = hostname_create(hostname);

	LOCK_HOSTLIST(hl);

	for (i = 0, count = 0; i < hl->nranges; i++) {
		if (hostrange_hn_within(hl->hr[i], hn)) {
			if (hostname_suffix_is_valid(hn))
				ret = count + hn->num - hl->hr[i]->lo;
			else
				ret = count;
			goto done;
		} else
			count += hostrange_count(hl->hr[i]);
	}

done:
	UNLOCK_HOSTLIST(hl);
	hostname_destroy(hn);
	return ret;
}
