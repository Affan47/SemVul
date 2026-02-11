quota_active_group_set_db(struct quota *q, struct group *g)
{
	if (group_is_active(g)) {
		gfarm_error_t e = db_quota_group_set(q, group_name(g));
		if (e == GFARM_ERR_NO_ERROR)
			q->on_db = 1;
		else
			gflog_error(GFARM_MSG_1000411,
				    "db_quota_group_set(%s) %s",
				    group_name(g), gfarm_error_string(e));
	}
}
