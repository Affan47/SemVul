gfarm_pgsql_group_modify(struct db_group_modify_arg *arg)
{
	struct gfarm_group_info *info = &arg->gi;
	gfarm_error_t e;
	static const char diag[] = "gfarm_pgsql_group_modify";

	if ((e = gfarm_pgsql_start_with_retry("pgsql_group_modify"))
	    == GFARM_ERR_NO_ERROR) {

		e = grpassign_remove(info->groupname);

		if (e == GFARM_ERR_NO_ERROR)
			e = grpassign_set(info);

		if (e == GFARM_ERR_NO_ERROR)
			e = gfarm_pgsql_commit(diag);
		else
			gfarm_pgsql_rollback(diag);
	}
	free(arg);
	return (e);
}
