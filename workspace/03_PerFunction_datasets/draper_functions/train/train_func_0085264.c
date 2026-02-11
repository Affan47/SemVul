ausearch_time_end(const char *da, const char *ti)
{


	int rc = 0;
	struct tm d, t;
	char *ret;

	if (da == NULL)
		set_tm_now(&d);
	else {
		if (lookup_and_set_time(da, &d) < 0) {
			ret = strptime(da, "%x", &d);
			if (ret == NULL) {
				fprintf(stderr,
		 "Invalid end date (%s). Month, Day, and Year are required.\n",
					da);
				return 1;
			}
			if (*ret != 0) {
				fprintf(stderr,
					"Error parsing end date (%s)\n", da);
				return 1;
			}
		} else {
			int keyword=lookup_time(da);
			if (keyword == T_RECENT || keyword == T_NOW) {
				if (ti == NULL || strcmp(ti, "00:00:00") == 0)
					goto set_it;
			}

			if (keyword == T_TODAY) {
				set_tm_now(&d);
				if (ti == NULL || strcmp(ti, "00:00:00") == 0)
					goto set_it;
			}
		}
	}

	if (ti != NULL) {
		char tmp_t[9];

		if (strlen(ti) <= 5) {
			snprintf(tmp_t, sizeof(tmp_t), "%s:00", ti);
		} else {
			tmp_t[0]=0;
			strncat(tmp_t, ti, sizeof(tmp_t)-1);
		}
		ret = strptime(tmp_t, "%X", &t);
		if (ret == NULL) {
			fprintf(stderr,
	     "Invalid end time (%s). Hour, Minute, and Second are required.\n",
				ti);
			return 1;
		}
		if (*ret != 0) {
			fprintf(stderr, "Error parsing end time (%s)\n", ti);
			return 1;
		}
	} else {
		time_t tt = time(NULL);
		struct tm *tv = localtime(&tt);
		clear_tm(&t);
		t.tm_hour = tv->tm_hour;
		t.tm_min = tv->tm_min;
		t.tm_sec = tv->tm_sec;
		t.tm_isdst = tv->tm_isdst;

	}
	add_tm(&d, &t);
	if (d.tm_year < 104) {
		fprintf(stderr, "Error - year is %d\n", d.tm_year+1900);
		return -1;
	}
set_it:

	end_time = mktime(&d);
	if (end_time == -1) {
		fprintf(stderr, "Error converting end time\n");
		rc = -1;
	}
	return rc;
}
