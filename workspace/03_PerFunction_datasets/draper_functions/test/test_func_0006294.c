ausearch_time_start(const char *da, const char *ti)
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
		"Invalid start date (%s). Month, Day, and Year are required.\n",
					da);
				return 1;
			}
			if (*ret != 0) {
				fprintf(stderr,
					"Error parsing start date (%s)\n", da);
				return 1;
			}
		} else {
			int keyword=lookup_time(da);
			if (keyword == T_RECENT || keyword == T_NOW) {
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
	"Invalid start time (%s). Hour, Minute, and Second are required.\n",
				ti);
			return 1;
		}
		if (*ret != 0) {
			fprintf(stderr, "Error parsing start time (%s)\n", ti);
			return 1;
		}
	} else
		clear_tm(&t);

	add_tm(&d, &t);
	if (d.tm_year < 104) {
		fprintf(stderr, "Error - year is %d\n", d.tm_year+1900);
		return -1;
	}
set_it:

	start_time = mktime(&d);
	if (start_time == -1) {
		fprintf(stderr, "Error converting start time\n");
		rc = -1;
	}
	return rc;
}
