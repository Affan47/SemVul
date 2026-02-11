new_DbEnv(u_int32_t flags){
		DB_ENV *self = NULL;
		errno = db_env_create(&self, flags);
		if (errno == 0)
			self->env->dbt_usercopy = __dbj_dbt_memcopy;
		return self;
	}
