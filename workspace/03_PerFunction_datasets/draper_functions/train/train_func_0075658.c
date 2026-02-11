check_command(gnutls_session_t session, const char *str)
{
	size_t len = strnlen(str, 128);
	int ret;

	fprintf(stderr, "*** Processing %u bytes command: %s\n", (unsigned)len,
		str);
	if (len > 2 && str[0] == str[1] && str[0] == '*') {
		if (strncmp
		    (str, "**REHANDSHAKE**",
		     sizeof("**REHANDSHAKE**") - 1) == 0) {
			fprintf(stderr,
				"*** Sending rehandshake request\n");
			gnutls_rehandshake(session);
			return 1;
		} else
		    if (strncmp
			(str, "**HEARTBEAT**",
			 sizeof("**HEARTBEAT**") - 1) == 0) {
			ret =
			    gnutls_heartbeat_ping(session, 300, 5,
						  GNUTLS_HEARTBEAT_WAIT);
			if (ret < 0) {
				if (ret == GNUTLS_E_INVALID_REQUEST) {
					fprintf(stderr,
						"No heartbeat in this session\n");
				} else {
					fprintf(stderr, "ping: %s\n",
						gnutls_strerror(ret));
					exit(1);
				}
			}
			return 2;
		}
	}
	return 0;
}
