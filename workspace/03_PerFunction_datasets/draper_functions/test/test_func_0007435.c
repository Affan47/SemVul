dpm_srv_rmfs(magic, req_data, clienthost, thip)
int magic;
char *req_data;
char *clienthost;
struct dpm_srv_thread_info *thip;
{
	char fs[80];
	struct dpm_fs fs_entry;
	char func[16];
	gid_t gid;
	gid_t *gids;
	char groups[256];
	char logbuf[CA_MAXHOSTNAMELEN+86];
	int nbgids;
	char *p;
	char *rbp;
	dpm_dbrec_addr rec_addr;
	char server[CA_MAXHOSTNAMELEN+1];
	uid_t uid;
	char *user;

	strcpy (func, "dpm_srv_rmfs");
	rbp = req_data;
	unmarshall_LONG (rbp, uid);
	unmarshall_LONG (rbp, gid);
	get_client_actual_id (thip, &uid, &gid, &nbgids, &gids, &user);
	p = Cencode_groups (nbgids, gids, groups, sizeof(groups));
	dpmlogit (func, DP092, "rmfs", user, uid, groups, clienthost);
	if (! p) {
		sendrep (thip->s, MSG_ERR, "Too many FQANs in proxy\n");
		RETURN (EINVAL);
	}
	if (unmarshall_STRINGN (rbp, server, CA_MAXHOSTNAMELEN+1) < 0)
		RETURN (EINVAL);
	if (unmarshall_STRINGN (rbp, fs, 80) < 0)
		RETURN (EINVAL);
	sprintf (logbuf, "rmfs %s %s", server, fs);
	dpm_logreq (func, logbuf);

	if (uid)
		RETURN (EACCES);

	if (strchr (server, '.') == NULL) {
		if (strlen (server) + strlen (localdomain) + 1 > CA_MAXHOSTNAMELEN)
			RETURN (EINVAL);
		strcat (server, ".");
		strcat (server, localdomain);
	}


	p = fs + strlen (fs) - 1;
	while (p > fs && *p == '/')
		*p-- = '\0';


	if (dpm_rmfsfrompoolconf (server, fs) < 0)
		RETURN (serrno);


	(void) dpm_start_tr (thip->s, &thip->dbfd);
	if (dpm_get_fs_entry (&thip->dbfd, server, fs, &fs_entry,
	    1, &rec_addr))
		RETURN (serrno);
	if (dpm_delete_fs_entry (&thip->dbfd, &rec_addr))
		RETURN (serrno);
	RETURN (0);
}
