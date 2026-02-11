wt_status_print_initial(struct wt_status *s)
{
	int i;
	struct strbuf buf = STRBUF_INIT;

	if (active_nr) {
		s->commitable = 1;
		wt_status_print_cached_header(s);
	}
	for (i = 0; i < active_nr; i++) {
		color_fprintf(s->fp, color(WT_STATUS_HEADER), "#\t");
		color_fprintf_ln(s->fp, color(WT_STATUS_UPDATED), "new file: %s",
				quote_path(active_cache[i]->name, -1,
					   &buf, s->prefix));
	}
	if (active_nr)
		wt_status_print_trailer(s);
	strbuf_release(&buf);
}
