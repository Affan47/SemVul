istgt_chap_get_authinfo(ISTGT_CHAP_AUTH *auth, const char *authfile, const char *authuser, int ag_tag)
{
	CONFIG *config = NULL;
	CF_SECTION *sp;
	const char *val;
	const char *user, *muser;
	const char *secret, *msecret;
	int rc;
	int i;

	if (auth->user != NULL) {
		xfree(auth->user);
		xfree(auth->secret);
		xfree(auth->muser);
		xfree(auth->msecret);
		auth->user = auth->secret = NULL;
		auth->muser = auth->msecret = NULL;
	}


	config = istgt_allocate_config();
	rc = istgt_read_config(config, authfile);
	if (rc < 0) {
		ISTGT_ERRLOG("auth conf error\n");
		istgt_free_config(config);
		return -1;
	}


	sp = config->section;
	while (sp != NULL) {
		if (sp->type == ST_AUTHGROUP) {
			if (sp->num == 0) {
				ISTGT_ERRLOG("Group 0 is invalid\n");
				istgt_free_config(config);
				return -1;
			}
			if (ag_tag != sp->num) {
				goto skip_ag_tag;
			}

			val = istgt_get_val(sp, "Comment");
			if (val != NULL) {
				ISTGT_TRACELOG(ISTGT_TRACE_DEBUG,
				    "Comment %s\n", val);
			}
			for (i = 0; ; i++) {
				val = istgt_get_nval(sp, "Auth", i);
				if (val == NULL)
					break;
				user = istgt_get_nmval(sp, "Auth", i, 0);
				secret = istgt_get_nmval(sp, "Auth", i, 1);
				muser = istgt_get_nmval(sp, "Auth", i, 2);
				msecret = istgt_get_nmval(sp, "Auth", i, 3);
				if (strcasecmp(authuser, user) == 0) {

					auth->user = xstrdup(user);
					auth->secret = xstrdup(secret);
					auth->muser = xstrdup(muser);
					auth->msecret = xstrdup(msecret);
					istgt_free_config(config);
					return 0;
				}
			}
		}
	skip_ag_tag:
		sp = sp->next;
	}

	istgt_free_config(config);
	return 0;
}
