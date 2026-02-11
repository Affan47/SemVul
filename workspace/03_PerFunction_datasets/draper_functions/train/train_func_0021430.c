Cns_srv_unlink(magic, req_data, clienthost, thip)
int magic;
char *req_data;
const char *clienthost;
struct Cns_srv_thread_info *thip;
{
	int c;
	u_signed64 cwd;
	struct Cns_file_metadata filentry;
	char func[16];
	gid_t gid;
	gid_t *gids;
	char groups[256];
	char logbuf[CA_MAXPATHLEN+8];
	int nbgids;
	char *p;
	struct Cns_file_metadata parent_dir;
	char path[CA_MAXPATHLEN+1];
	char *rbp;
	Cns_dbrec_addr rec_addr;
	Cns_dbrec_addr rec_addrp;
	uid_t uid;
	char *user;

	strcpy (func, "Cns_srv_unlink");
	rbp = req_data;
	unmarshall_LONG (rbp, uid);
	unmarshall_LONG (rbp, gid);
	get_client_actual_id (thip, &uid, &gid, &nbgids, &gids, &user);
	p = Cencode_groups (nbgids, gids, groups, sizeof(groups));
	nslogit (func, NS092, "unlink", user, uid, groups, clienthost);
	if (! p) {
		sendrep (thip->s, MSG_ERR, "Too many FQANs in proxy\n");
		RETURN (EINVAL);
	}
	if (rdonly)
		RETURN (EROFS);
	unmarshall_HYPER (rbp, cwd);
	if (unmarshall_STRINGN (rbp, path, CA_MAXPATHLEN+1))
		RETURN (SENAMETOOLONG);
	sprintf (logbuf, "unlink %s", path);
	Cns_logreq (func, logbuf);


	(void) Cns_start_tr (thip->s, &thip->dbfd);


	if (Cns_parsepath (&thip->dbfd, cwd, path, uid, nbgids, gids, clienthost,
	    &parent_dir, &rec_addrp, &filentry, &rec_addr, CNS_MUST_EXIST|CNS_NOFOLLOW))
		RETURN (serrno);

	c = unlinkonefile (thip, uid, nbgids, gids, clienthost,
	    &parent_dir, rec_addrp, &filentry, rec_addr, 0);
	RETURN (c);
}
