aim_locate_dorequest(aim_session_t *sess)
{
	struct userinfo_node *cur = sess->locate.request_queue;

	if (cur == NULL)
		return;

	if (sess->locate.waiting_for_response == TRUE)
		return;

	sess->locate.waiting_for_response = TRUE;
	aim_locate_getinfoshort(sess, cur->sn, 0x00000007);
}
