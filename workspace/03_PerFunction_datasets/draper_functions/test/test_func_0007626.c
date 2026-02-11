jogger_usedchanged(session_t *s, const char *varname) {
	const char *tmp, *tmpb;

	session_t *js = session_find((tmp = session_get(s, "used_session")));

	if (!js) {
#if 0
		print("jogger_wrong_session", tmp);
		session_connected_set(s, 0);
		session_status_set(s, EKG_STATUS_ERROR);
#endif
		return;
	}

	if (xstrcmp((tmpb = session_uid_get(js)), tmp))
		session_set(s, "used_session", tmpb);


	if (!(tmpb = get_uid(js, (tmp = session_get(s, "used_uid"))))) {
#if 0
		print("jogger_wrong_uid", tmp);
		session_connected_set(s, 0);
		session_status_set(s, EKG_STATUS_ERROR);
#endif
		return;
	}

	if (xstrcmp(tmpb, tmp))
		session_set(s, "used_uid", tmpb);

	{
		userlist_t *u	= userlist_find(js, tmpb);

		if (session_connected_get(s) != (u && (u->status > EKG_STATUS_NA))) {
			session_connected_set(s, (u && (u->status > EKG_STATUS_NA)));
			session_status_set(s, (u ? u->status : EKG_STATUS_NA));
		}
	}
}
