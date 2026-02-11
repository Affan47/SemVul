compare(const void* _a, const void* _b) {
    const AvahiTimeEvent *a = _a,  *b = _b;
    int ret;

    if ((ret = avahi_timeval_compare(&a->expiry, &b->expiry)) != 0)
        return ret;


    return avahi_timeval_compare(&a->last_run, &b->last_run);
}
