domove(int by)
{
    char *msgid;
    char s[SIZE_s+1];

    by = (by < 0) ? -1 : 1;
    if (group) {
	if (artno) {
	    artno += by;
	    do {
		sprintf(s, "%lu", artno);
		msgid = getheader(s, "Message-ID:");
		if (!msgid)
		    artno += by;
	    } while (msgid == NULL && artno >= group->first && artno <= group->last);
	    if (msgid && (artno > group->last || artno < group->first)) {
		free(msgid);
		msgid = NULL;
	    }
	    if (msgid == NULL) {
		if (by > 0) {
		    artno = group->last;
		    printf("421 There is no next article\r\n");
		    if (debugmode)
			syslog(LOG_DEBUG, ">421 There is no next article");
		} else {
		    artno = group->first;
		    printf("422 There is no previous article\r\n");
		    if (debugmode)
			syslog(LOG_DEBUG, ">422 There is no previous article");
		}
	    } else {
		printf("223 %lu %s article retrieved\r\n", artno, msgid);
		if (debugmode)
		    syslog(LOG_DEBUG, ">223 %lu %s article retrieved",
			   artno, msgid);
		free(msgid);
	    }
	} else {
	    printf("420 There is no current article\r\n");
	    if (debugmode)
		syslog(LOG_DEBUG, ">420 There is no current article");
	}
    } else {
	nogroup();
    }
}
