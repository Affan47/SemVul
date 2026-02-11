lookup_format(const char *fmt)
{
	struct trace_bprintk_fmt *pos;

	if (!fmt)
		return ERR_PTR(-EINVAL);

	list_for_each_entry(pos, &trace_bprintk_fmt_list, list) {
		if (!strcmp(pos->fmt, fmt))
			return pos;
	}
	return NULL;
}
