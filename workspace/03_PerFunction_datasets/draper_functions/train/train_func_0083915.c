syslogin_perform_login(struct logininfo *li)
{
	struct utmp *ut;

	if (! (ut = (struct utmp *)malloc(sizeof(*ut)))) {
		dropbear_log(LOG_WARNING, "syslogin_perform_login: couldn't malloc()");
		return 0;
	}
	construct_utmp(li, ut);
	login(ut);
	free(ut);

	return 1;
}
