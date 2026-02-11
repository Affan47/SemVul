mprServiceEvents(MprTime timeout, int flags)
{
    MprEventService     *es;
    MprDispatcher       *dp;
    MprTime             expires, delay;
    int                 beginEventCount, eventCount, justOne;

    if (MPR->eventing) {
        mprError("mprServiceEvents() called reentrantly");
        return 0;
    }
    MPR->eventing = 1;
    mprInitWindow();
    es = MPR->eventService;
    beginEventCount = eventCount = es->eventCount;

    es->now = mprGetTime();
    expires = timeout < 0 ? MAXINT64 : (es->now + timeout);
    if (expires < 0) {
        expires = MAXINT64;
    }
    justOne = (flags & MPR_SERVICE_ONE_THING) ? 1 : 0;

    while (es->now < expires && !mprIsStoppingCore()) {
        eventCount = es->eventCount;
        if (MPR->signalService->hasSignals) {
            mprServiceSignals();
        }
        while ((dp = getNextReadyDispatcher(es)) != NULL) {
            mprAssert(!dp->destroyed);
            mprAssert(dp->magic == MPR_DISPATCHER_MAGIC);
            if (!serviceDispatcher(dp)) {
                queueDispatcher(es->pendingQ, dp);
                continue;
            }
            if (justOne) {
                return abs(es->eventCount - beginEventCount);
            }
        }
        if (es->eventCount == eventCount) {
            lock(es);
            delay = getIdleTime(es, expires - es->now);
            if (delay > 0) {
                es->waiting = 1;
                es->willAwake = es->now + delay;
                unlock(es);
                if (mprIsStopping()) {
                    if (mprServicesAreIdle()) {
                        break;
                    }
                    delay = 10;
                }
                mprWaitForIO(MPR->waitService, delay);
            } else {
                unlock(es);
            }
        }
        es->now = mprGetTime();
        if (justOne) {
            break;
        }
    }
    MPR->eventing = 0;
    return abs(es->eventCount - beginEventCount);
}
