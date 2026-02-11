manageWaitHandler(MprWaitHandler *wp, int flags)
{
    if (flags & MPR_MANAGE_MARK) {
        mprMark(wp->handlerData);
        mprMark(wp->dispatcher);
        mprMark(wp->service);
        mprMark(wp->next);
        mprMark(wp->prev);
        mprMark(wp->requiredWorker);
        mprMark(wp->thread);
        mprMark(wp->callbackComplete);
        mprMark(wp->event);

    } else if (flags & MPR_MANAGE_FREE) {
        mprRemoveWaitHandler(wp);
    }
}
