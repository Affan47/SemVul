download_gui_rescheduling(char *buf, size_t buflen, const struct download *d)
{
	char resched[80];
	time_t rescheduled;


	rescheduled = d->last_update + d->timeout_delay;
	rescheduled = MAX(rescheduled, d->retry_after);

	time_locale_to_string_buf(rescheduled, resched, sizeof resched);

	if (NULL == d->remove_msg) {
		str_bprintf(buf, buflen, "%s %s #%u",
			delta_time(rescheduled, tm_time()) > 0 ?
				_("Rescheduled for") : _("Restartable since"),
			lazy_locale_to_ui_string(resched), d->retries);
	} else {
		str_bprintf(buf, buflen, "%s - %s %s #%u",
			d->remove_msg,
			delta_time(rescheduled, tm_time()) > 0 ?
				_("rescheduled for") : _("restartable since"),
			lazy_locale_to_ui_string(resched), d->retries);
	}

	return buf;
}
