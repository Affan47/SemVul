bam_parse_region(bam_header_t *header, const char *str, int *ref_id, int *begin, int *end)
{
	char *s, *p;
	int i, l, k;
	khiter_t iter;
	khash_t(s) *h;

	bam_init_header_hash(header);
	h = (khash_t(s)*)header->hash;

	l = strlen(str);
	p = s = (char*)malloc(l+1);

	for (i = k = 0; i != l; ++i)
		if (str[i] != ',' && !isspace(str[i])) s[k++] = str[i];
	s[k] = 0;
	for (i = 0; i != k; ++i) if (s[i] == ':') break;
	s[i] = 0;
	iter = kh_get(s, h, s);
	if (iter == kh_end(h)) {
		*ref_id = -1; free(s);
		return -1;
	}
	*ref_id = kh_value(h, iter);
	if (i == k) {
		*begin = 0; *end = 1<<29; free(s);
		return 0;
	}
	for (p = s + i + 1; i != k; ++i) if (s[i] == '-') break;
	*begin = atoi(p);
	if (i < k) {
		p = s + i + 1;
		*end = atoi(p);
	} else *end = 1<<29;
	if (*begin > 0) --*begin;
	free(s);
	if (*begin > *end) {
		fprintf(stderr, "[bam_parse_region] invalid region.\n");
		return -1;
	}
	return 0;
}
