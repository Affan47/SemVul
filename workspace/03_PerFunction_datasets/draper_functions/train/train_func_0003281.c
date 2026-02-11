null_login(unit)
    int unit;
{
    char *filename;
    FILE *f;
    int i, ret;
    struct wordlist *addrs, *opts;
    char secret[MAXWORDLEN];


    ret = -1;
    if (null_auth_hook)
	ret = (*null_auth_hook)(&addrs, &opts);


    if (ret <= 0) {
	filename = _PATH_UPAPFILE;
	addrs = NULL;
	f = fopen(filename, "r");
	if (f == NULL)
	    return 0;
	check_access(f, filename);

	i = scan_authfile(f, "", our_name, secret, &addrs, &opts, filename, 0);
	ret = i >= 0 && secret[0] == 0;
	BZERO(secret, sizeof(secret));
	fclose(f);
    }

    if (ret)
	set_allowed_addrs(unit, addrs, opts);
    else if (opts != 0)
	free_wordlist(opts);
    if (addrs != 0)
	free_wordlist(addrs);

    return ret;
}
