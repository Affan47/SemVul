icalenum_reqstat_code_r(icalrequeststatus stat)
{
    int i, major, minor;
    char tmpbuf[36];

    for (i=0; request_status_map[i].kind  != ICAL_UNKNOWN_STATUS; i++) {
	if ( request_status_map[i].kind ==  stat) {
	    major = request_status_map[i].major;
	    minor = request_status_map[i].minor;
	    snprintf(tmpbuf, sizeof(tmpbuf), "%i.%i", major, minor);
	    return icalmemory_strdup(tmpbuf);
	}
    }
    return NULL;
}
