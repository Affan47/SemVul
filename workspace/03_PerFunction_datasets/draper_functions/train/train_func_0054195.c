user_time(char *ptr)
{
	const struct utmp *usr;
	time_t log_in, real, diff;
	char buf[BUFLEN] = "";

	setutent();
	while ((usr = getutent()) != NULL) {
		if (usr->ut_type == USER_PROCESS) {
			log_in = usr->ut_time;
			time(&real);
			diff = difftime(real, log_in);
			format_seconds(buf, BUFLEN, diff);
			if (strlen(ptr) + strlen(buf) + 1 <= BUFLEN) {
				strncat(ptr, buf, BUFLEN-strlen(ptr)-1);
			}
		}
	}
}
