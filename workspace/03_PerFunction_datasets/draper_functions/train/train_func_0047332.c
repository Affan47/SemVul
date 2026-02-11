__env_thread_destroy(env)
	ENV *env;
{
	DB_HASHTAB *htab;
	DB_THREAD_INFO *ip, *np;
	REGENV *renv;
	REGINFO *infop;
	THREAD_INFO *thread;
	u_int32_t i;

	infop = env->reginfo;
	renv = infop->primary;
	if (renv->thread_off == INVALID_ROFF)
		return;

	thread = R_ADDR(infop, renv->thread_off);
	if ((htab = env->thr_hashtab) != NULL) {
		for (i = 0; i < env->thr_nbucket; i++) {
			ip = SH_TAILQ_FIRST(&htab[i], __db_thread_info);
			for (; ip != NULL; ip = np) {
				np = SH_TAILQ_NEXT(ip,
				    dbth_links, __db_thread_info);
				__env_alloc_free(infop, ip);
			}
		}
		__env_alloc_free(infop, htab);
	}

	__env_alloc_free(infop, thread);
	return;
}
