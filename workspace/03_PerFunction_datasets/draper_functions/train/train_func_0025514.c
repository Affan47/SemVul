aim_cachecookie(aim_session_t *sess, aim_msgcookie_t *cookie)
{
	aim_msgcookie_t *newcook;

	if (!sess || !cookie)
		return -EINVAL;

	newcook = aim_checkcookie(sess, cookie->cookie, cookie->type);

	if (newcook == cookie) {
		newcook->addtime = time(NULL);
		return 1;
	} else if (newcook)
		aim_cookie_free(sess, newcook);

	cookie->addtime = time(NULL);

	cookie->next = sess->msgcookies;
	sess->msgcookies = cookie;

	return 0;
}
