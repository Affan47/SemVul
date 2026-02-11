php_logo_guid(void)
{
	char *logo_guid;

	time_t the_time;
	struct tm *ta, tmbuf;

	the_time = time(NULL);
	ta = php_localtime_r(&the_time, &tmbuf);

	if (ta && (ta->tm_mon==3) && (ta->tm_mday==1)) {
		logo_guid = PHP_EGG_LOGO_GUID;
	} else {
		logo_guid = PHP_LOGO_GUID;
	}

	return estrdup(logo_guid);

}
