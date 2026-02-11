dpm_getstatus_putreq (char *r_token, int nbtosurls, char **tosurls, int *nbreplies, struct dpm_putfilestatus **filestatuses)
{
	int c;
	char errstring[256];
	char func[21];
	gid_t gid;
	int i;
	int msglen;
	char *rbp;
	char repbuf[4+256];
	char *sbp;
	char *sendbuf;
	char surl[CA_MAXSFNLEN+1];
	struct dpm_api_thread_info *thip;
	uid_t uid;

	strcpy (func, "dpm_getstatus_putreq");
	if (dpm_apiinit (&thip))
		return (-1);
	uid = geteuid();
	gid = getegid();
#if defined(_WIN32)
	if (uid < 0 || gid < 0) {
		dpm_errmsg (func, DP053);
		serrno = SENOMAPFND;
		return (-1);
	}
#endif

	if (nbtosurls < 0) {
		serrno = EINVAL;
		return (-1);
	}
	if ((nbtosurls && ! tosurls) ||
	    ! r_token || ! nbreplies || ! filestatuses) {
		serrno = EFAULT;
		return (-1);
	}


	msglen = 5 * LONGSIZE;
	msglen += strlen (r_token) + 1;
	msglen += LONGSIZE;
	for (i = 0; i < nbtosurls; i++) {
		msglen += strlen (tosurls[i]) + 1;
	}


	if ((sendbuf = malloc (msglen)) == NULL) {
		serrno = ENOMEM;
		return (-1);
	}


	sbp = sendbuf;
	marshall_LONG (sbp, DPM_MAGIC2);
	marshall_LONG (sbp, DPM_GETSTSPUT);
	marshall_LONG (sbp, msglen);


	marshall_LONG (sbp, uid);
	marshall_LONG (sbp, gid);
	marshall_STRING (sbp, r_token);
	marshall_LONG (sbp, nbtosurls);
	for (i = 0; i < nbtosurls; i++) {
		marshall_STRING (sbp, tosurls[i]);
	}
	c = send2dpm (NULL, sendbuf, msglen, repbuf, sizeof(repbuf),
	    (void **)filestatuses, nbreplies);
	free (sendbuf);

	if (c == 0) {
		rbp = repbuf;
		unmarshall_LONG (rbp, c);
		if ((c & 0xF000) == DPM_FAILED) {
			serrno = c - DPM_FAILED;
			c = -1;
		}
		unmarshall_STRING (rbp, errstring);
		if (*errstring)
			dpm_errmsg (func, "%s\n", errstring);
	}
	return (c);
}
