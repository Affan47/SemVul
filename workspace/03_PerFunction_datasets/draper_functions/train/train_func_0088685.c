scan_service(const char *fn, time_t now)
{
	struct outgoing *o;
	FILE *f;
	int res;

	o = new_outgoing(fn);
	if (!o) {
		return -1;
	}


	f = fopen(o->fn, "r");
	if (!f) {
#if defined(HAVE_INOTIFY) || defined(HAVE_KQUEUE)


		if (errno != ENOENT)
#endif
		{
			ast_log(LOG_WARNING, "Unable to open %s: '%s'(%d), deleting\n",
				o->fn, strerror(errno), (int) errno);
		}
		remove_from_queue(o, "Failed");
		free_outgoing(o);
		return -1;
	}


	res = apply_outgoing(o, f);
	fclose(f);
	if (res) {
		ast_log(LOG_WARNING, "Invalid file contents in %s, deleting\n", o->fn);
		remove_from_queue(o, "Failed");
		free_outgoing(o);
		return -1;
	}

	ast_debug(1, "Filename: %s, Retries: %d, max: %d\n", o->fn, o->retries, o->maxretries);
	if (o->retries <= o->maxretries) {
		now += o->retrytime;
		if (o->callingpid && (o->callingpid == ast_mainpid)) {
			safe_append(o, time(NULL), "DelayedRetry");
			ast_debug(1, "Delaying retry since we're currently running '%s'\n", o->fn);
			free_outgoing(o);
		} else {

			o->retries++;


			if (o->callingpid)
				safe_append(o, time(NULL), "AbortRetry");

			safe_append(o, now, "StartRetry");
			launch_service(o);
		}
		return now;
	}

	ast_log(LOG_NOTICE, "Queued call to %s/%s expired without completion after %d attempt%s\n",
		o->tech, o->dest, o->retries - 1, ((o->retries - 1) != 1) ? "s" : "");
	remove_from_queue(o, "Expired");
	free_outgoing(o);
	return 0;
}
