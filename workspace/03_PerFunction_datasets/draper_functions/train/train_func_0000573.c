dpm_srv_inc_reqctr(magic, req_data, clienthost, thip)
int magic;
char *req_data;
char *clienthost;
struct dpm_srv_thread_info *thip;
{
	int c;
	char func[19];
	gid_t gid;
	gid_t *gids;
	char groups[256];
	int nbgids;
	char *p;
	char *rbp;
	uid_t uid;
	char *user;

	strcpy (func, "dpm_srv_inc_reqctr");
	rbp = req_data;
	unmarshall_LONG (rbp, uid);
	unmarshall_LONG (rbp, gid);
	get_client_actual_id (thip, &uid, &gid, &nbgids, &gids, &user);
	p = Cencode_groups (nbgids, gids, groups, sizeof(groups));
	dpmlogit (func, DP092, "inc_reqctr", user, uid, groups, clienthost);
	if (! p) {
		sendrep (thip->s, MSG_ERR, "Too many FQANs in proxy\n");
		RETURN (EINVAL);
	}

	c = inc_reqctr ();
	RETURN (c);
}
