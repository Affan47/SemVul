__os_ufree(env, ptr)
	ENV *env;
	void *ptr;
{
	DB_ENV *dbenv;

	dbenv = env == NULL ? NULL : env->dbenv;

	if (dbenv != NULL && dbenv->db_free != NULL)
		dbenv->db_free(ptr);
	else if (DB_GLOBAL(j_free) != NULL)
		DB_GLOBAL(j_free)(ptr);
	else
		free(ptr);
}
