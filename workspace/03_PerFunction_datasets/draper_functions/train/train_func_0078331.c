re_wrap(void)
{
	int w = width;
	int new_line_pos;
	int src_idx;
	int dst_idx;
	int new_cur_fline = 0;
	uint32_t lineno;
	char linebuf[w + 1];
	const char **old_flines = flines;
	const char *s;
	char **new_flines = NULL;
	char *d;

	if (option_mask32 & FLAG_N)
		w -= 8;

	src_idx = 0;
	dst_idx = 0;
	s = old_flines[0];
	lineno = LINENO(s);
	d = linebuf;
	new_line_pos = 0;
	while (1) {
		*d = *s;
		if (*d != '\0') {
			new_line_pos++;
			if (*d == '\t')
				new_line_pos += 7;
			s++;
			d++;
			if (new_line_pos >= w) {
				int sz;

				*d = '\0';
 next_new:
				sz = (d - linebuf) + 1;
				d = ((char*)xmalloc(sz + 4)) + 4;
				LINENO(d) = lineno;
				memcpy(d, linebuf, sz);
				new_flines = xrealloc_vector(new_flines, 8, dst_idx);
				new_flines[dst_idx] = d;
				dst_idx++;
				if (new_line_pos < w) {

					if (src_idx > max_fline)
						break;
					lineno = LINENO(s);
				}
				d = linebuf;
				new_line_pos = 0;
			}
			continue;
		}

		free(MEMPTR(old_flines[src_idx]));

		if (cur_fline == src_idx)
			new_cur_fline = dst_idx;
		src_idx++;

		if (src_idx > max_fline)
			goto next_new;
		s = old_flines[src_idx];
		if (lineno != LINENO(s)) {


			goto next_new;
		}
	}

	free(old_flines);
	flines = (const char **)new_flines;

	max_fline = dst_idx - 1;
	last_line_pos = new_line_pos;
	cur_fline = new_cur_fline;

#if ENABLE_FEATURE_LESS_REGEXP
	pattern_valid = 0;
#endif
}
