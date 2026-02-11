get_upap_passwd()
{
    char *filename;
    FILE *f;
    struct wordlist *addrs;
    char secret[MAXWORDLEN];

    filename = _PATH_UPAPFILE;
    addrs = NULL;
    f = fopen(filename, "r");
    if (f == NULL)
	return 0;
    check_access(f, filename);
    if (scan_authfile(f, user, remote_name, secret, NULL, filename) < 0)
	return 0;
    strncpy(passwd, secret, MAXSECRETLEN);
    passwd[MAXSECRETLEN-1] = 0;
    return 1;
}
