get_sha1_basic(const char *str, int len, unsigned char *sha1)
{
	static const char *warning = "warning: refname '%.*s' is ambiguous.\n";
	char *real_ref = NULL;
	int refs_found = 0;
	int at, reflog_len;

	if (len == 40 && !get_sha1_hex(str, sha1))
		return 0;


	reflog_len = at = 0;
	if (str[len-1] == '}') {
		for (at = 0; at < len - 1; at++) {
			if (str[at] == '@' && str[at+1] == '{') {
				reflog_len = (len-1) - (at+2);
				len = at;
				break;
			}
		}
	}


	if (len && ambiguous_path(str, len))
		return -1;

	if (!len && reflog_len) {

		refs_found = dwim_ref("HEAD", 4, sha1, &real_ref);
	} else if (reflog_len)
		refs_found = dwim_log(str, len, sha1, &real_ref);
	else
		refs_found = dwim_ref(str, len, sha1, &real_ref);

	if (!refs_found)
		return -1;

	if (warn_ambiguous_refs && refs_found > 1)
		fprintf(stderr, warning, len, str);

	if (reflog_len) {
		int nth, i;
		unsigned long at_time;
		unsigned long co_time;
		int co_tz, co_cnt;


		for (i = nth = 0; 0 <= nth && i < reflog_len; i++) {
			char ch = str[at+2+i];
			if ('0' <= ch && ch <= '9')
				nth = nth * 10 + ch - '0';
			else
				nth = -1;
		}
		if (0 <= nth)
			at_time = 0;
		else
			at_time = approxidate(str + at + 2);
		if (read_ref_at(real_ref, at_time, nth, sha1, NULL,
				&co_time, &co_tz, &co_cnt)) {
			if (at_time)
				fprintf(stderr,
					"warning: Log for '%.*s' only goes "
					"back to %s.\n", len, str,
					show_rfc2822_date(co_time, co_tz));
			else
				fprintf(stderr,
					"warning: Log for '%.*s' only has "
					"%d entries.\n", len, str, co_cnt);
		}
	}

	free(real_ref);
	return 0;
}
