symmetric_encryption_xfer(int csock, int s_in, int s_out) {
	char tmp[100];
	char *cipher, *keyfile, *q;

	if (! enc_str) {
		return;
	}
	cipher = (char *) malloc(strlen(enc_str) + 100);
	q = strchr(enc_str, ':');
	if (!q) return;
	*q = '\0';
	if (getenv("X11VNC_USE_ULTRADSM_IV")) {
		sprintf(cipher, "rev:%s", enc_str);
	} else {
		sprintf(cipher, "noultra:rev:%s", enc_str);
	}
	keyfile = strdup(q+1);
	*q = ':';


	if (s_out) {}

	sprintf(tmp, "fd=%d,%d", s_in, csock);

	enc_do(cipher, keyfile, "-1", tmp);
}
