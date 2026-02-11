senddata_raw(int socket,const char *buffer, int length) {
#if !(defined(WIN32) && !defined(CYGWIN))
	int rc;

	for(rc=0;rc < length;) {
		rc = TEMP_FAILURE_RETRY(
			send(socket,&buffer[rc],length-rc,MSG_NOSIGNAL));
		if(CHECK_RC(rc))
			return -1;
	}

	return length;
#endif
#if defined(WIN32) && !defined(CYGWIN)
	int rc;

	for(rc=0;rc < length;) {
		rc = TEMP_FAILURE_RETRY(send(socket, buffer, length-rc, 0));
		if(CHECK_RC(rc))
			return -1;
	}
	return length;
#endif
}
