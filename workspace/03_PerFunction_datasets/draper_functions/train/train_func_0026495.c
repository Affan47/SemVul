check_notify_failure(struct check *check)
{
	struct server *s = check->server;


	if ((check->state & CHK_ST_AGENT) && check->status != HCHK_STATUS_L7STS)
		return;

	if (check->health > 0)
		return;


	srv_set_stopped(s, (!s->track && !(s->proxy->options2 & PR_O2_LOGHCHKS)) ? check_reason_string(check) : NULL);
}
