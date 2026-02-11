mprRelayEvent(MprDispatcher *dispatcher, void *proc, void *data, MprEvent *event)
{
#if BLD_DEBUG
    MprThread   *tp = mprGetCurrentThread();
    mprNop(tp);
#endif
    mprAssert(!isRunning(dispatcher));
    mprAssert(dispatcher->owner == 0);
    mprAssert(dispatcher->magic == MPR_DISPATCHER_MAGIC);
    mprAssert(!dispatcher->destroyed);

    if (event) {
        event->timestamp = dispatcher->service->now;
    }
    dispatcher->enabled = 1;
    dispatcher->owner = mprGetCurrentOsThread();
    makeRunnable(dispatcher);
    ((MprEventProc) proc)(data, event);
    scheduleDispatcher(dispatcher);
    dispatcher->owner = 0;
}
