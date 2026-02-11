header_features_generate(xfeature_t xf, char *dst, size_t len, size_t *rw)
{
	static const char hdr[] = "X-Features";
	struct features *features;
	GList *cur;
	header_fmt_t *fmt;

	g_assert(len <= INT_MAX);
	g_assert(*rw <= INT_MAX);
	g_assert(len >= *rw);

	if (len - *rw < (sizeof(hdr) + sizeof(": \r\n") - 1))
		return;

	features = features_get(xf);
	g_return_if_fail(features);

	if (g_list_first(features->list) == NULL)
		return;

	fmt = header_fmt_make(hdr, ", ", 0, len - *rw);

	for (cur = g_list_first(features->list); cur; cur = g_list_next(cur)) {
		struct header_x_feature *item = cur->data;
		char buf[50];

		if (item->guard && !*item->guard)
			continue;

		if (item->guardfn && !(*item->guardfn)())
			continue;

		str_bprintf(buf, sizeof buf, "%s/%d.%d",
			item->name, item->major, item->minor);

		header_fmt_append_value(fmt, buf);
	}

	header_fmt_end(fmt);

	if (header_fmt_length(fmt) < len - *rw) {
		*rw += clamp_strncpy(&dst[*rw], len - *rw,
				header_fmt_string(fmt), header_fmt_length(fmt));
	}

	header_fmt_free(&fmt);
}
