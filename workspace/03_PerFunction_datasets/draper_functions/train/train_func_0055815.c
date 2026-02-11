infadd_start(void *v)
{
    AddThread *at = (AddThread *)v;
    PRIntervalTime timer;
    PRUint32 span, i;
    int notBound = 1;
    int ret;


    if (blobsize > 0) {
        at->blob = (char *)malloc(blobsize);
        if (! at->blob) {
            fprintf(stderr, "T%d: can't allocate blob!\n", at->id);
            return;
        }
        for (i = 0; i < blobsize; i++)
            at->blob[i] = (char)(rand() & 0xff);
    }

    at->alive = 1;
    while (1) {
        timer = PR_IntervalNow();


        if (notBound) {
            at_bind(at);
            if (noDelay)
                at_enableTCPnodelay(at);
            notBound = 0;
        }

        ret = at_add(at);
        if (LDAP_SUCCESS == ret) {
            span = PR_IntervalToMilliseconds(PR_IntervalNow()-timer);

            PR_Lock(at->lock);
            at->addCount++;
            at->addTotal++;
            if (at->mintime > span)
                at->mintime = span;
            if (at->maxtime < span)
                at->maxtime = span;
            at->alive = 1;
            at->retry = 0;
            PR_Unlock(at->lock);
        } else if (LDAP_CONNECT_ERROR == ret && at->retry < 10) {
            PR_Lock(at->lock);
            at->retry++;
            PR_Unlock(at->lock);
        } else {
            at_bail(at);
            return;
        }

    }
}
