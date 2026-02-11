PERMinfile(hp, ip, user, pass, accesslist)
    char		*hp;
    char		*ip;
    char		*user;
    char		*pass;
    char		*accesslist;
{
    static char		ACCESS[] = _PATH_NNRPACCESS;
    register FILE	*F;
    register char	*p;
    register BOOL	found;
    register int	i;
    struct passwd	*pwd;
    char		buff[BIG_BUFFER];
    char		*fields[5];

    if ((F = fopen(ACCESS, "r")) == NULL) {
	syslog(L_ERROR, "%s cant fopen %s %m", ClientHost, ACCESS);
	return FALSE;
    }

    PERMcanread = FALSE;
    PERMcanpost = FALSE;
    found = FALSE;
    accesslist[0] = '\0';
    while (fgets(buff, sizeof buff, F) != NULL) {
	if ((p = strchr(buff, '\n')) != NULL)
	    *p = '\0';
	if ((p = strchr(buff, COMMENT_CHAR)) != NULL)
	    *p = '\0';
	if (buff[0] == '\0')
	    continue;


	for (fields[0] = buff, i = 0, p = buff; *p; p++)
	    if (*p == ':') {
		*p = '\0';
		fields[++i] = p + 1;
	    }
	if (i != 4)

	    continue;

	if (hp)


	    if (!(ip && wildmat(ip, fields[0])) && !wildmat(hp, fields[0]))
		continue;


	if (user && pass && EQ(fields[2], "+")) {
	    if ((pwd = getpwnam(user)) == NULL)
		continue;
	    if (!EQ(pwd->pw_passwd, crypt(pass, pwd->pw_passwd)))
		continue;
	}

	else if (user && (!EQ(user, fields[2]) || !EQ(pass, fields[3])))
	    continue;

	PERMcanread = strchr(fields[1], 'R') != NULL;
	PERMcanpost = strchr(fields[1], 'P') != NULL;
	(void)strcpy(PERMuser, user ? user : fields[2]);
	(void)strcpy(PERMpass, pass ? pass : fields[3]);
	(void)strcpy(accesslist, fields[4]);
	found = TRUE;
    }
    (void)fclose(F);
    return found;
}
