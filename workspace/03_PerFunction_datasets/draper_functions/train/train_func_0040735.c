dispatchEvents(MprDispatcher *dispatcher)
{
    MprEventService     *es;
    MprEvent            *event;
    int                 count;

    mprAssert(dispatcher->enabled);
    mprAssert(dispatcher->cond);
    mprAssert(!dispatcher->destroyed);

    es = dispatcher->service;
    LOG(7, "dispatchEvents for %s", dispatcher->name);

    lock(es);
    for (count = 0; (event = mprGetNextEvent(dispatcher)) != 0; count++) {
        mprAssert(event->magic == MPR_EVENT_MAGIC);
        dispatcher->current = event;
        if (event->continuous) {

            event->timestamp = dispatcher->service->now;
            event->due = event->timestamp + (event->period ? event->period : 1);
            mprQueueEvent(dispatcher, event);
        }
        mprAssert(event->proc);
        unlock(es);
        LOG(7, "Call event %s", event->name);
        (event->proc)(event->data, event);
        dispatcher->current = 0;
        lock(es);
    }
    unlock(es);
    if (count && es->waiting) {
        es->eventCount += count;
        mprWakeNotifier();
    }
    return count;
}
