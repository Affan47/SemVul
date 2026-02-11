user_fetch(dynalogin_user_data_t **ud,
		const dynalogin_userid_t userid,
		apr_pool_t *pool)
{
	if(strcmp((char *)userid, u_tester.userid) == 0)
		*ud = &u_tester;
	else
		*ud = (dynalogin_user_data_t *)NULL;

	syslog(LOG_DEBUG, "user = %s, count = %d", userid, u_tester.counter);
	return;
}
