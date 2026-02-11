ast_str_encode_mime(struct ast_str **end, ssize_t maxlen, const char *start, size_t preamble, size_t postamble)
{
	struct ast_str *tmp = ast_str_alloca(80);
	int first_section = 1;

	ast_str_reset(*end);
	ast_str_set(&tmp, -1, "=?%s?Q?", charset);
	for (; *start; start++) {
		int need_encoding = 0;
		if (*start < 33 || *start > 126 || strchr("()<>@,:;/\"[]?.=_", *start)) {
			need_encoding = 1;
		}
		if ((first_section && need_encoding && preamble + ast_str_strlen(tmp) > 70) ||
			(first_section && !need_encoding && preamble + ast_str_strlen(tmp) > 72) ||
			(!first_section && need_encoding && ast_str_strlen(tmp) > 70) ||
			(!first_section && !need_encoding && ast_str_strlen(tmp) > 72)) {

			ast_str_append(end, maxlen, "%s%s?=", first_section ? "" : " ", ast_str_buffer(tmp));
			ast_str_set(&tmp, -1, "=?%s?Q?", charset);
			first_section = 0;
		}
		if (need_encoding && *start == ' ') {
			ast_str_append(&tmp, -1, "_");
		} else if (need_encoding) {
			ast_str_append(&tmp, -1, "=%hhX", *start);
		} else {
			ast_str_append(&tmp, -1, "%c", *start);
		}
	}
	ast_str_append(end, maxlen, "%s%s?=%s", first_section ? "" : " ", ast_str_buffer(tmp), ast_str_strlen(tmp) + postamble > 74 ? " " : "");
	return ast_str_buffer(*end);
}
