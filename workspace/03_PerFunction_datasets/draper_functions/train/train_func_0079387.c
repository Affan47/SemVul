__rep_find_dbs(env, context)
	ENV *env;
	FILE_LIST_CTX *context;
{
	DB_ENV *dbenv;
	int ret;
	char **ddir, *real_dir;

	dbenv = env->dbenv;
	ret = 0;
	real_dir = NULL;


	if (!F_ISSET(context, FILE_CTX_INMEM_ONLY) &&
	    dbenv->db_data_dir != NULL) {
		for (ddir = dbenv->db_data_dir; *ddir != NULL; ++ddir) {
			if ((ret = __db_appname(env,
			    DB_APP_NONE, *ddir, NULL, &real_dir)) != 0)
				break;
			if ((ret = __rep_walk_dir(env,
			    real_dir, *ddir, context)) != 0)
				break;
			__os_free(env, real_dir);
			real_dir = NULL;
		}
	}


	if (!F_ISSET(context, FILE_CTX_INMEM_ONLY) && ret == 0)
		ret = __rep_walk_dir(env, env->db_home, NULL, context);


	if (ret == 0)
		ret = __rep_walk_dir(env, NULL, NULL, context);

	if (real_dir != NULL)
		__os_free(env, real_dir);
	return (ret);
}
