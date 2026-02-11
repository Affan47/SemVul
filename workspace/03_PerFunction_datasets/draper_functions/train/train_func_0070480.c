Cns_srv_chdir(magic, req_data, clienthost, thip)
int magic;
char *req_data;
const char *clienthost;
struct Cns_srv_thread_info *thip;
{
	u_signed64 cwd;
	struct Cns_file_metadata direntry;
	char func[16];
	gid_t gid;
	gid_t *gids;
	char groups[256];
	char logbuf[CA_MAXPATHLEN+12];
	int nbgids;
	char *p;
	char path[CA_MAXPATHLEN+1];
	char *rbp;
	char repbuf[8];
	char *sbp;
	uid_t uid;
	char *user;

	strcpy (func, "Cns_srv_chdir");
	rbp = req_data;
	unmarshall_LONG (rbp, uid);
	unmarshall_LONG (rbp, gid);
	get_client_actual_id (thip, &uid, &gid, &nbgids, &gids, &user);
	p = Cencode_groups (nbgids, gids, groups, sizeof(groups));
	nslogit (func, NS092, "chdir", user, uid, groups, clienthost);
	if (! p) {
		sendrep (thip->s, MSG_ERR, "Too many FQANs in proxy\n");
		RETURN (EINVAL);
	}
	unmarshall_HYPER (rbp, cwd);
	if (unmarshall_STRINGN (rbp, path, CA_MAXPATHLEN+1))
		RETURN (SENAMETOOLONG);
	sprintf (logbuf, "chdir %s", path);
	Cns_logreq (func, logbuf);


	if (Cns_parsepath (&thip->dbfd, cwd, path, uid, nbgids, gids, clienthost,
	    NULL, NULL, &direntry, NULL, CNS_MUST_EXIST))
		RETURN (serrno);

	if ((direntry.filemode & S_IFDIR) == 0)
		RETURN (ENOTDIR);
	if (Cns_chkentryperm (&direntry, S_IEXEC, uid, nbgids, gids, clienthost))
		RETURN (EACCES);


	sbp = repbuf;
	marshall_HYPER (sbp, direntry.fileid);
	sendrep (thip->s, MSG_DATA, sbp - repbuf, repbuf);
	RETURN (0);
}
