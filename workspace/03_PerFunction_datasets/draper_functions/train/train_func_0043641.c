thread_join( long long tid, void *status)
#else
void *
thread_join( tid, status)
long long tid;
void *status;
#endif
{
	int xx;
	pthread_t eek;
	pthread_attr_t foo;

	bcopy(&p_childids[tid],&eek,sizeof(pthread_t));
	xx=pthread_join(eek,(void **)&foo);
	if(xx<0)
		printf("Thread join returned error %d\n",errno);
	return(0);
}
