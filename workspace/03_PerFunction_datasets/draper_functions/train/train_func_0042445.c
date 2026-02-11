bitmap2node_name_sortable (bitstr_t *bitmap, bool sort)
{
	int i, first, last;
	hostlist_t hl;
	char *buf;

	if (bitmap == NULL)
		return xstrdup("");

	first = bit_ffs(bitmap);
	if (first == -1)
		return xstrdup("");

	last  = bit_fls(bitmap);
	hl = hostlist_create("");
	for (i = first; i <= last; i++) {
		if (bit_test(bitmap, i) == 0)
			continue;
		hostlist_push(hl, node_record_table_ptr[i].name);
	}
	if (sort)
		hostlist_sort(hl);
	buf = hostlist_ranged_string_xmalloc(hl);
	hostlist_destroy(hl);

	return buf;
}
