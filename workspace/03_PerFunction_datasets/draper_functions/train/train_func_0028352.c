__env_faultmem(env, addr, size, created)
	ENV *env;
	void *addr;
	size_t size;
	int created;
{
	int ret;
	u_int8_t *p, *t;


	if (F_ISSET(env, ENV_PRIVATE))
		return (0);


	ret = 0;
	if (F_ISSET(env->dbenv, DB_ENV_REGION_INIT)) {
		if (created)
			for (p = addr,
			    t = (u_int8_t *)addr + size; p < t; p += 512)
				p[0] = 0xdb;
		else
			for (p = addr,
			    t = (u_int8_t *)addr + size; p < t; p += 512)
				ret |= p[0];
	}

	return (ret);
}
