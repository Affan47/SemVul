rb_time_timeval(VALUE time)
{
    struct time_object *tobj;
    struct timeval t;
    struct timespec ts;

    if (IsTimeval(time)) {
	GetTimeval(time, tobj);
        ts = timew2timespec(tobj->timew);
        t.tv_sec = (TYPEOF_TIMEVAL_TV_SEC)ts.tv_sec;
        t.tv_usec = (TYPEOF_TIMEVAL_TV_USEC)(ts.tv_nsec / 1000);
	return t;
    }
    return time_timeval(time, FALSE);
}
