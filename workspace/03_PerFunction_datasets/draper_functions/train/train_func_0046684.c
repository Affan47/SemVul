t_pool_destroy(t_pool *p, int kill) {
    int i;

#ifdef DEBUG
    fprintf(stderr, "Destroying pool %p, kill=%d\n", p, kill);
#endif


    if (!kill) {
	pthread_mutex_lock(&p->pool_m);
	p->shutdown = 1;

#ifdef DEBUG
	fprintf(stderr, "Sending shutdown request\n");
#endif

	pthread_cond_broadcast(&p->pending_c);
	pthread_mutex_unlock(&p->pool_m);

#ifdef DEBUG
	fprintf(stderr, "Shutdown complete\n");
#endif
	for (i = 0; i < p->tsize; i++)
	    pthread_join(p->t[i], NULL);
    } else {
	for (i = 0; i < p->tsize; i++)
	    pthread_kill(p->t[i], SIGINT);
    }

    pthread_mutex_destroy(&p->pool_m);
    pthread_cond_destroy(&p->empty_c);
    pthread_cond_destroy(&p->pending_c);
    pthread_cond_destroy(&p->full_c);

#ifdef DEBUG_TIME
    fprintf(stderr, "Total time=%f\n", p->total_time / 1000000.0);
    fprintf(stderr, "Wait  time=%f\n", p->wait_time  / 1000000.0);
    fprintf(stderr, "%d%% utilisation\n",
	    (int)(100 - ((100.0 * p->wait_time) / p->total_time + 0.5)));
#endif

    free(p->t);
    free(p);

#ifdef DEBUG
    fprintf(stderr, "Destroyed pool %p\n", p);
#endif
}
