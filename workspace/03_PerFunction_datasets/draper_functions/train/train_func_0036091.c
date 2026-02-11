mprResumeThreads()
{
    MprThreadService    *ts;
    MprThread           *tp;
    int                 i;

    ts = MPR->threadService;
    LOG(7, "mprResumeThreadsAfterGC sync");

    mprLock(ts->mutex);
    for (i = 0; i < ts->threads->length; i++) {
        tp = (MprThread*) mprGetItem(ts->threads, i);
        if (tp && tp->yielded) {
            if (!tp->stickyYield) {
                tp->yielded = 0;
            }
            mprSignalCond(tp->cond);
        }
    }
    mprUnlock(ts->mutex);
}
