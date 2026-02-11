get_secret(unit, client, server, secret, secret_len, save_addrs)
    int unit;
    char *client;
    char *server;
    char *secret;
    int *secret_len;
    int save_addrs;
{
    FILE *f;
    int ret, len;
    char *filename;
    struct wordlist *addrs;
    char secbuf[MAXWORDLEN];

    filename = _PATH_CHAPFILE;
    addrs = NULL;
    secbuf[0] = 0;

    f = fopen(filename, "r");
    if (f == NULL) {
	syslog(LOG_ERR, "Can't open chap secret file %s: %m", filename);
	return 0;
    }
    check_access(f, filename);

    ret = scan_authfile(f, client, server, (u_int32_t)0,
			secbuf, &addrs, filename);
    fclose(f);
    if (ret < 0)
	return 0;

    if (save_addrs)
	set_allowed_addrs(unit, addrs);

    len = strlen(secbuf);
    if (len > MAXSECRETLEN) {
	syslog(LOG_ERR, "Secret for %s on %s is too long", client, server);
	len = MAXSECRETLEN;
    }
    BCOPY(secbuf, secret, len);
    BZERO(secbuf, sizeof(secbuf));
    *secret_len = len;

    return 1;
}
