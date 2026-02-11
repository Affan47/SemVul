mprCreateEvent(MprDispatcher *dispatcher, cchar *name, MprTime period, void *proc, void *data, int flags)
{
    MprEvent    *event;

    if ((event = mprAllocObj(MprEvent, manageEvent)) == 0) {
        return 0;
    }
    if (dispatcher == 0) {
        dispatcher = (flags & MPR_EVENT_QUICK) ? MPR->nonBlock : MPR->dispatcher;
    }
    initEvent(dispatcher, event, name, period, proc, data, flags);
    if (!(flags & MPR_EVENT_DONT_QUEUE)) {
        mprQueueEvent(dispatcher, event);
    }
    return event;
}
