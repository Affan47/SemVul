JimELAssocDataDeleProc(Jim_Interp *interp, void *data)
{
    void *next;
    Jim_FileEvent *fe;
    Jim_TimeEvent *te;
    Jim_EventLoop *eventLoop = data;

    fe = eventLoop->fileEventHead;
    while (fe) {
        next = fe->next;
        if (fe->finalizerProc)
            fe->finalizerProc(interp, fe->clientData);
        Jim_Free(fe);
        fe = next;
    }

    te = eventLoop->timeEventHead;
    while (te) {
        next = te->next;
        if (te->finalizerProc)
            te->finalizerProc(interp, te->clientData);
        Jim_Free(te);
        te = next;
    }
    Jim_Free(data);
}
