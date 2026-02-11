script_input(void)
{
	char buf[128];
	int nr;
	char *ptr;
	char c;

	trace_dsn("Input for %s[%d] %d\n", ST_NAME, sms_depth, sms->state);


	if (sms->is_socket)
		nr = recv(sms->infd, buf, sizeof(buf), 0);
	else
		nr = read(sms->infd, buf, sizeof(buf));
	if (nr < 0) {
#if defined(_WIN32)
	    	if (sms->is_socket)
		    	popup_an_error("%s[%d] recv: %s", ST_NAME, sms_depth,
				win32_strerror(GetLastError()));
		else
#endif
		popup_an_errno(errno, "%s[%d] read", ST_NAME, sms_depth);
		return;
	}
	if (nr == 0) {
		trace_dsn("EOF %s[%d]\n", ST_NAME, sms_depth);
		sms_pop(True);
		sms_continue();
		return;
	}


	ptr = buf;
	while (nr--)
		if ((c = *ptr++) != '\r')
			sms->msc[sms->msc_len++] = c;


	sms->state = SS_INCOMPLETE;
	sms_continue();
}
