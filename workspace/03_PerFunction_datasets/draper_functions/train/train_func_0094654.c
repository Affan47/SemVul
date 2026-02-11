check_passwd(unit, auser, userlen, apasswd, passwdlen, msg, msglen)
    int unit;
    char *auser;
    int userlen;
    char *apasswd;
    int passwdlen;
    char **msg;
    int *msglen;
{
    int ret;
    char *filename;
    FILE *f;
    struct wordlist *addrs;
    u_int32_t remote;
    ipcp_options *ipwo = &ipcp_wantoptions[unit];
    char passwd[256], user[256];
    char secret[MAXWORDLEN];
    static int attempts = 0;


    BCOPY(apasswd, passwd, passwdlen);
    passwd[passwdlen] = '\0';
    BCOPY(auser, user, userlen);
    user[userlen] = '\0';
    *msg = (char *) 0;


    filename = _PATH_UPAPFILE;
    addrs = NULL;
    ret = UPAP_AUTHACK;
    f = fopen(filename, "r");
    if (f == NULL) {
	syslog(LOG_ERR, "Can't open PAP password file %s: %m", filename);
	ret = UPAP_AUTHNAK;

    } else {
	check_access(f, filename);
	remote = ipwo->accept_remote? 0: ipwo->hisaddr;
	if (scan_authfile(f, user, our_name, remote,
			  secret, &addrs, filename) < 0
	    || (secret[0] != 0 && (cryptpap || strcmp(passwd, secret) != 0)
		&& strcmp(crypt(passwd, secret), secret) != 0)) {
	    syslog(LOG_WARNING, "PAP authentication failure for %s", user);
	    ret = UPAP_AUTHNAK;
	}
	fclose(f);
    }

    if (uselogin && ret == UPAP_AUTHACK) {
	ret = plogin(user, passwd, msg, msglen);
	if (ret == UPAP_AUTHNAK) {
	    syslog(LOG_WARNING, "PAP login failure for %s", user);
	}
    }

    if (ret == UPAP_AUTHNAK) {
        if (*msg == (char *) 0)
	    *msg = "Login incorrect";
	*msglen = strlen(*msg);


	if (attempts++ >= 10) {
	    syslog(LOG_WARNING, "%d LOGIN FAILURES ON %s, %s",
		   attempts, devnam, user);
	    quit();
	}
	if (attempts > 3)
	    sleep((u_int) (attempts - 3) * 5);
	if (addrs != NULL)
	    free_wordlist(addrs);

    } else {
	attempts = 0;
	if (*msg == (char *) 0)
	    *msg = "Login ok";
	*msglen = strlen(*msg);
	set_allowed_addrs(unit, addrs);
    }

    BZERO(passwd, sizeof(passwd));
    BZERO(secret, sizeof(secret));

    return ret;
}
