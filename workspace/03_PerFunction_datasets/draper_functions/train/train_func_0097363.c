aeDeleteFileEvent(aeEventLoop *eventLoop, int fd, int mask)
{
    aeFileEvent *fe, *prev = NULL;

    fe = eventLoop->fileEventHead;
    while(fe) {
        if (fe->fd == fd && fe->mask == mask) {
            if (prev == NULL)
                eventLoop->fileEventHead = fe->next;
            else
                prev->next = fe->next;
            if (fe->finalizerProc)
                fe->finalizerProc(eventLoop, fe->clientData);
            zfree(fe);
            return;
        }
        prev = fe;
        fe = fe->next;
    }
}
