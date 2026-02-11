parseLogErrs(UINT16_t type, UINT16_t len, unsigned char *data,
	     void *extra)
{
    switch(type) {
    case TAG_SERVICE_NAME_ERROR:
	syslog(LOG_ERR, "PADT: Service-Name-Error: %.*s", (int) len, data);
	fprintf(stderr, "PADT: Service-Name-Error: %.*s\n", (int) len, data);
	break;
    case TAG_AC_SYSTEM_ERROR:
	syslog(LOG_ERR, "PADT: System-Error: %.*s", (int) len, data);
	fprintf(stderr, "PADT: System-Error: %.*s\n", (int) len, data);
	break;
    case TAG_GENERIC_ERROR:
	syslog(LOG_ERR, "PADT: Generic-Error: %.*s", (int) len, data);
	fprintf(stderr, "PADT: Generic-Error: %.*s\n", (int) len, data);
	break;
    }
}
