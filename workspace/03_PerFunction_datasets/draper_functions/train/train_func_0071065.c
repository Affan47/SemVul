workq_destroy(workq_t *wq)
{
int	status, status1, status2;

    if ( wq->valid != WORKQ_VALID )
	return EINVAL;

    status = pthread_mutex_lock(&wq->mutex);
    if ( status != 0 )
	return(status);
    wq->valid = 0;


    if ( wq->counter > 0 ) {
	wq->quit = 1;
	if ( wq->idle > 0 ) {
	    status = pthread_cond_broadcast(&wq->cv);
	    if ( status != 0 ) {
	        pthread_mutex_unlock(&wq->mutex);
	        return(status);
	    }
	}
	while ( wq->counter > 0 ) {
	    status = pthread_cond_wait(&wq->cv, &wq->mutex);
	    if ( status != 0 ) {
	        pthread_mutex_unlock(&wq->mutex);
	        return(status);
	    }
	}
    }
    status = pthread_mutex_unlock(&wq->mutex);
    if ( status != 0 )
	return(status);
    status = pthread_mutex_destroy(&wq->mutex);
    status1 = pthread_cond_destroy(&wq->cv);
    status2 = pthread_attr_destroy(&wq->attr);
    return(status?status:(status1?status1:status2));
}
