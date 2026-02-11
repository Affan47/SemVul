mdb_close(MDB_env *env, MDB_dbi dbi)
{
	char *ptr;
	if (dbi <= MAIN_DBI || dbi >= env->me_numdbs)
		return;
	ptr = env->me_dbxs[dbi].md_name.mv_data;
	env->me_dbxs[dbi].md_name.mv_data = NULL;
	env->me_dbxs[dbi].md_name.mv_size = 0;
	free(ptr);
}
