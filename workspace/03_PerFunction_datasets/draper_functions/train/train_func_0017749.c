dpm_getpoolfs(char *poolname, int *nbfs, struct dpm_fs **dpm_fs)
{
	int c;
	char func[16];
	gid_t gid;
	int i;
	int msglen;
	char *p;
	char *q;
	char *rbp;
	char repbuf[1];
	char *sbp;
	char sendbuf[REQBUFSZ];
	struct dpm_api_thread_info *thip;
	uid_t uid;

	strcpy (func, "dpm_getpoolfs");
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

	if (! poolname || ! nbfs || ! dpm_fs) {
		serrno = EFAULT;
		return (-1);
	}


	sbp = sendbuf;
	marshall_LONG (sbp, DPM_MAGIC2);
	marshall_LONG (sbp, DPM_GETPOOLFS);
	q = sbp;
	msglen = 3 * LONGSIZE;
	marshall_LONG (sbp, msglen);


	marshall_LONG (sbp, uid);
	marshall_LONG (sbp, gid);
	marshall_STRING (sbp, poolname);

	msglen = sbp - sendbuf;
	marshall_LONG (q, msglen);

	c = send2dpm (NULL, sendbuf, msglen, repbuf, sizeof(repbuf),
	    (void **)dpm_fs, nbfs);
	return (c);
}
