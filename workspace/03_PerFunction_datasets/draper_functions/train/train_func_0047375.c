tp_exit(struct tp_data **tdatp)
{
	struct tp_data *tdat = *tdatp;
	void *ret;

	if (!tdat)
		return;

	pthread_mutex_lock(&tdat->lock);
	tdat->thread_exit = 1;
	pthread_mutex_unlock(&tdat->lock);

	pthread_cond_signal(&tdat->cv);

	pthread_join(tdat->thread, &ret);

	sfree(tdat);
	*tdatp = NULL;
}
