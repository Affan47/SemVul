backslash_escape(const char *src, char **templates, unsigned int template_count)
{
	char *src_dup;
	const char *p;
	unsigned int dup_idx = 0, dup_len;

	dup_len = strlen(src) + 1;
	src_dup = malloc(dup_len * sizeof(char));

	p = src;
	while (*p) {
		switch (*p) {
		case '\\':
			if (!*(p + 1))
				break;
			if (*(p + 1) == '\\') {
				src_dup[dup_idx++] = '\\';
				p++;
			} else if (*(p + 1) == ' ') {
				src_dup[dup_idx++] = ' ';
				p++;
			} else if (*(p + 1) == 'n') {
				src_dup[dup_idx++] = '\n';
				p++;
			} else if (templates) {
				unsigned int tmpl_num;
				int digits;
				if ((sscanf(p + 1, "%u%n", &tmpl_num, &digits) <= 0) ||
				    (tmpl_num > template_count))
					break;
				dup_len += strlen(templates[tmpl_num - 1]);
				src_dup = realloc(src_dup, dup_len * sizeof(char));
				sprintf(src_dup + dup_idx, "%s", templates[tmpl_num - 1]);
				dup_idx += strlen(templates[tmpl_num - 1]);
				p += digits;
			}
			break;
		default:
			src_dup[dup_idx++] = *p;
			break;
		}
		p++;
	}
	src_dup[dup_idx] = '\0';
	src_dup = realloc(src_dup, (strlen(src_dup) + 1) * sizeof(char));
	return src_dup;
}
