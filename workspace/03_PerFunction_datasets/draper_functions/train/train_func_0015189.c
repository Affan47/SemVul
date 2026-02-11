term_deinit(void)
{
	if (current_term != NULL) {
		signal(SIGCONT, SIG_DFL);
		g_source_destroy(sigcont_source);
		g_source_unref(sigcont_source);

		term_common_deinit();
		terminfo_core_deinit(current_term);
		current_term = NULL;
	}
}
