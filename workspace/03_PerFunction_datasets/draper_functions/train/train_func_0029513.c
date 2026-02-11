get_rpq_timezone(void)
{


	time_t here;
	struct tm here_tm;
	struct tm *utc_tm;
	double delta;
	char *p1, *p2;
	struct rpq_keyword *kw;


	for (kw = &rpq_keywords[0]; kw -> id != RPQ_TIMEZONE; kw++) {
	}


	if ((kw->allow_oride) && (kw->oride > 0)) {
		ldiv_t hhmm;
		long x;

		p1 = x3270rpq+kw->oride;

		x = strtol(p1, &p2, 10);
		if (errno != 0) {
			rpq_warning("RPQ TIMEZONE term is invalid - "
					"use +/-hhmm");
			return 4;
		}
		if ((*p2 != '\0') && (*p2 != ':') && (!isspace(*p2)))
			return 4;

		hhmm = ldiv(x, 100L);

		if (hhmm.rem > 59L) {
			rpq_warning("RPQ TIMEZONE term is invalid - "
					"use +/-hhmm");
			return 4;
		}

		delta = (labs(hhmm.quot) * 60L) + hhmm.rem;
		if (hhmm.quot < 0L) delta = -delta;
	} else {


		if ((here = time(NULL)) == (time_t)(-1)) {
			rpq_warning("RPQ: Unable to determine workstation "
					"local time");
			return 1;
		}
		memcpy(&here_tm, localtime(&here), sizeof(struct tm));
		if ((utc_tm = gmtime(&here)) == NULL) {
			rpq_warning("RPQ: Unable to determine workstation UTC "
					"time");
			return 2;
		}


		here_tm.tm_isdst = 0;
		utc_tm->tm_isdst = 0;
		delta = difftime(mktime(&here_tm), mktime(utc_tm)) / 60L;
	}


	if (labs(delta) > 720L)
		rpq_warning("RPQ timezone exceeds 12 hour UTC offset");
	return (labs(delta) > 720L)? 3 : (int) delta;
}
