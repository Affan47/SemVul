aim_locate_finduserinfo(aim_session_t *sess,
	const char *sn)
{
	aim_userinfo_t *cur = sess->locate.userinfo;

	while (cur != NULL) {
		if (aim_sncmp(cur->sn, sn) == 0)
			return cur;
		cur = cur->next;
	}

	return NULL;
}
