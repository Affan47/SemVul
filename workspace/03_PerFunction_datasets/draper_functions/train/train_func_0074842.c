toplevel_run_diff_runner(gpointer data)
{
	struct run_datum *run = data;
	poldiff_t *diff = sediffx_get_poldiff(run->top->s, progress_poldiff_handle_func, run->top->progress);
	if (diff == NULL) {
		run->result = -1;
		progress_abort(run->top->progress, "Could not get a poldiff object: %s", strerror(errno));
		return NULL;
	}
	run->result = poldiff_run(diff, run->run_flags);
	sediffx_set_poldiff_run_flags(run->top->s, run->run_flags);
	if (run->run_flags & (POLDIFF_DIFF_AVRULES | POLDIFF_DIFF_TERULES)) {
		poldiff_enable_line_numbers(diff);
	}
	if (run->result < 0) {
		progress_abort(run->top->progress, NULL);
	} else {
		progress_done(run->top->progress);
	}
	return NULL;
}
