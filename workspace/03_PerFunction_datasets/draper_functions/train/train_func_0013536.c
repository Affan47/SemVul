_get_bracketed_list(hostlist_t hl, int *start, const size_t n, char *buf)
{
	hostrange_t *hr = hl->hr;
	int i = *start;
	int m, len = 0;
	int bracket_needed = _is_bracket_needed(hl, i);
	int zeropad = 0;
	uint32_t cluster_flags = slurmdb_setup_cluster_flags();

	if (cluster_flags & CLUSTER_FLAG_CRAYXT) {


		zeropad = _zero_padded(hr[i]->hi, hr[i]->width);


		for (m = i + 1; zeropad && m < hl->nranges; m++) {
			int pad = 0;

			if (!hostrange_within_range(hr[m], hr[m-1]))
				break;
			if (hl->hr[m]->width == hl->hr[m-1]->width)
				pad = _zero_padded(hr[m]->hi, hr[m]->width);
			if (pad < zeropad)
				zeropad = pad;
		}
	}

	if (zeropad)
		len = snprintf(buf, n, "%s%0*u", hr[i]->prefix, zeropad, 0);
	else
		len = snprintf(buf, n, "%s", hr[i]->prefix);
	if (len < 0 || len + 4 >= n)
		return n;

	if (bracket_needed)
		buf[len++] = '[';

	do {
		if (i > *start)
			buf[len++] = ',';
		m = hostrange_numstr(hr[i], n - len, buf + len, zeropad);
		if (m < 0 || (len += m) >= n - 1)
			return n;
	} while (++i < hl->nranges && hostrange_within_range(hr[i], hr[i-1]));

	if (bracket_needed)
		buf[len++] = ']';

	buf[len] = '\0';
	*start = i;
	return len;
}
