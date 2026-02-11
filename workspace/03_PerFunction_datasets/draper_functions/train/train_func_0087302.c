attempt_thread(void *data)
{
	struct outgoing *o = data;
	int res, reason;
	if (!ast_strlen_zero(o->app)) {
		ast_verb(3, "Attempting call on %s/%s for application %s(%s) (Retry %d)\n", o->tech, o->dest, o->app, o->data, o->retries);
		res = ast_pbx_outgoing_app(o->tech, o->capabilities, o->dest, o->waittime * 1000,
			o->app, o->data, &reason, 2 , o->cid_num, o->cid_name,
			o->vars, o->account, NULL);
		o->vars = NULL;
	} else {
		ast_verb(3, "Attempting call on %s/%s for %s@%s:%d (Retry %d)\n", o->tech, o->dest, o->exten, o->context,o->priority, o->retries);
		res = ast_pbx_outgoing_exten(o->tech, o->capabilities, o->dest,
			o->waittime * 1000, o->context, o->exten, o->priority, &reason,
			2 , o->cid_num, o->cid_name, o->vars, o->account, NULL,
			ast_test_flag(&o->options, SPOOL_FLAG_EARLY_MEDIA));
		o->vars = NULL;
	}
	if (res) {
		ast_log(LOG_NOTICE, "Call failed to go through, reason (%d) %s\n", reason, ast_channel_reason2str(reason));
		if (o->retries >= o->maxretries + 1) {

			ast_log(LOG_NOTICE, "Queued call to %s/%s expired without completion after %d attempt%s\n", o->tech, o->dest, o->retries - 1, ((o->retries - 1) != 1) ? "s" : "");
			remove_from_queue(o, "Expired");
		} else {

			safe_append(o, time(NULL), "EndRetry");
#if defined(HAVE_INOTIFY) || defined(HAVE_KQUEUE)
			queue_file(o->fn, time(NULL) + o->retrytime);
#endif
		}
	} else {
		ast_log(LOG_NOTICE, "Call completed to %s/%s\n", o->tech, o->dest);
		remove_from_queue(o, "Completed");
	}
	free_outgoing(o);
	return NULL;
}
