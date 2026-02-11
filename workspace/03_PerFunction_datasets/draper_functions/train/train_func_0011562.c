hdhomerun_debug_set_prefix(struct hdhomerun_debug_t *dbg, const char *prefix)
{
	if (!dbg) {
		return;
	}

	pthread_mutex_lock(&dbg->print_lock);

	if (dbg->prefix) {
		free(dbg->prefix);
		dbg->prefix = NULL;
	}

	if (prefix) {
		dbg->prefix = strdup(prefix);
	}

	pthread_mutex_unlock(&dbg->print_lock);
}
