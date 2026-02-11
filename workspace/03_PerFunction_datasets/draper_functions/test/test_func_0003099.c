pgc(void)
{
	static time_t last_run;
	time_t now;

	if (NULL == pool_gc)
		return;


	now = tm_time();
	if (last_run == now)
		return;
	last_run = now;

	hash_list_foreach(pool_gc, pool_gc_trampoline, NULL);
	hash_list_free(&pool_gc);
}
