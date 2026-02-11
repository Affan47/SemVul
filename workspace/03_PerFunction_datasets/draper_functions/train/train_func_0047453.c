dpm_srv_getprotocols(magic, req_data, clienthost, thip)
int magic;
char *req_data;
char *clienthost;
struct dpm_srv_thread_info *thip;
{
	char func[21];
	gid_t gid;
	gid_t *gids;
	char groups[256];
	int i;
	int nbgids;
	char *p;
	char *rbp;
	char repbuf[256];
	char *sbp;
	uid_t uid;
	char *user;

	strcpy (func, "dpm_srv_getprotocols");
	rbp = req_data;
	unmarshall_LONG (rbp, uid);
	unmarshall_LONG (rbp, gid);
	get_client_actual_id (thip, &uid, &gid, &nbgids, &gids, &user);
	p = Cencode_groups (nbgids, gids, groups, sizeof(groups));
	dpmlogit (func, DP092, "getprotocols", user, uid, groups, clienthost);
	if (! p) {
		sendrep (thip->s, MSG_ERR, "Too many FQANs in proxy\n");
		RETURN (EINVAL);
	}

	sbp = repbuf;
	marshall_WORD (sbp, nb_supported_protocols);
	for (i = 0; i < nb_supported_protocols; i++) {
		marshall_STRING (sbp, supported_protocols[i]);
	}
	sendrep (thip->s, MSG_DATA, sbp - repbuf, repbuf);
	RETURN (0);
}
