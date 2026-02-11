heim_base_once_f(heim_base_once_t *once, void *ctx, void (*func)(void *))
{
#ifdef HAVE_DISPATCH_DISPATCH_H
    dispatch_once_f(once, ctx, func);
#else
    static HEIMDAL_MUTEX mutex = HEIMDAL_MUTEX_INITIALIZER;
    HEIMDAL_MUTEX_lock(&mutex);
    if (*once == 0) {
	*once = 1;
	HEIMDAL_MUTEX_unlock(&mutex);
	func(ctx);
	HEIMDAL_MUTEX_lock(&mutex);
	*once = 2;
	HEIMDAL_MUTEX_unlock(&mutex);
    } else if (*once == 2) {
	HEIMDAL_MUTEX_unlock(&mutex);
    } else {
	HEIMDAL_MUTEX_unlock(&mutex);
	while (1) {
	    struct timeval tv = { 0, 1000 };
	    select(0, NULL, NULL, NULL, &tv);
	    HEIMDAL_MUTEX_lock(&mutex);
	    if (*once == 2)
		break;
	    HEIMDAL_MUTEX_unlock(&mutex);
	}
	HEIMDAL_MUTEX_unlock(&mutex);
    }
#endif
}
