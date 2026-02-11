ne_rfc1123_date(time_t anytime) {
    struct tm *gmt;
    char *ret;
    gmt = gmtime(&anytime);
    if (gmt == NULL)
	return NULL;
    ret = ne_malloc(29 + 1);

    ne_snprintf(ret, 30, RFC1123_FORMAT,
		rfc1123_weekdays[gmt->tm_wday], gmt->tm_mday,
		short_months[gmt->tm_mon], 1900 + gmt->tm_year,
		gmt->tm_hour, gmt->tm_min, gmt->tm_sec);

    return ret;
}
