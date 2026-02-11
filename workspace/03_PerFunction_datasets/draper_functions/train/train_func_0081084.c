health_adjust(struct server *s, short status) {

	int failed;
	int expire;


	if (!s->observe || !s->check)
		return;

	if (s->observe >= HANA_OBS_SIZE)
		return;

	if (status >= HANA_STATUS_SIZE || !analyze_statuses[status].desc)
		return;

	switch (analyze_statuses[status].lr[s->observe - 1]) {
		case 1:
			failed = 1;
			break;

		case 2:
			failed = 0;
			break;

		default:
			return;
	}

	if (!failed) {

		s->consecutive_errors = 0;
		return;
	}

	s->consecutive_errors++;

	if (s->consecutive_errors < s->consecutive_errors_limit)
		return;

	sprintf(trash, "Detected %d consecutive errors, last one was: %s",
		s->consecutive_errors, get_analyze_status(status));

	switch (s->onerror) {
		case HANA_ONERR_FASTINTER:

			break;

		case HANA_ONERR_SUDDTH:

			if (s->health > s->rise)
				s->health = s->rise + 1;


		case HANA_ONERR_FAILCHK:

			set_server_check_status(s, HCHK_STATUS_HANA, trash);

			if (s->health > s->rise) {
				s->health--;
				s->counters.failed_checks++;
			}
			else
				set_server_down(s);

			break;

		case HANA_ONERR_MARKDWN:

			s->health = s->rise;
			set_server_check_status(s, HCHK_STATUS_HANA, trash);
			set_server_down(s);

			break;

		default:

			break;
	}

	s->consecutive_errors = 0;
	s->counters.failed_hana++;

	if (s->fastinter) {
		expire = tick_add(now_ms, MS_TO_TICKS(s->fastinter));
		if (s->check->expire > expire)
			s->check->expire = expire;
	}
}
