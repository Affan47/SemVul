gretl_errmsg_set (const char *str)
{
#if EDEBUG
    fprintf(stderr, "gretl_errmsg_set: '%s'\n", str);
#endif

    if (alarm_set && *gretl_errmsg != '\0') {

	return;
    }

    if (*gretl_errmsg == '\0') {
	strncat(gretl_errmsg, str, ERRLEN - 1);
    } else if (strcmp(gretl_errmsg, str)) {

	int n = strlen(gretl_errmsg);
	int m = strlen(str);

	if (n + m + 2 < ERRLEN) {
	    strcat(gretl_errmsg, "\n");
	    strcat(gretl_errmsg, str);
	}
    }

#if EDEBUG
    fprintf(stderr, "gretl_errmsg now: '%s'\n", gretl_errmsg);
#endif
}
