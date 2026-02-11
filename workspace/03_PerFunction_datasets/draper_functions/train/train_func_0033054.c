ast_rtp_lookup_mime_multiple2(struct ast_str *buf, struct ast_format_cap *ast_format_capability, int rtp_capability, const int asterisk_format, enum ast_rtp_options options)
{
	int found = 0;
	const char *name;
	if (!buf) {
		return NULL;
	}


	if (asterisk_format) {
		struct ast_format tmp_fmt;
		ast_format_cap_iter_start(ast_format_capability);
		while (!ast_format_cap_iter_next(ast_format_capability, &tmp_fmt)) {
			name = ast_rtp_lookup_mime_subtype2(asterisk_format, &tmp_fmt, 0, options);
			ast_str_append(&buf, 0, "%s|", name);
			found = 1;
		}
		ast_format_cap_iter_end(ast_format_capability);

	} else {
		int x;
		ast_str_append(&buf, 0, "0x%x (", (unsigned int) rtp_capability);
		for (x = 1; x <= AST_RTP_MAX; x <<= 1) {
			if (rtp_capability & x) {
				name = ast_rtp_lookup_mime_subtype2(asterisk_format, NULL, x, options);
				ast_str_append(&buf, 0, "%s|", name);
				found = 1;
			}
		}
	}

	ast_str_append(&buf, 0, "%s", found ? ")" : "nothing)");

	return ast_str_buffer(buf);
}
