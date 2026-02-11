Jim_eventloopInit(Jim_Interp *interp)
{
    Jim_EventLoop *eventLoop;

    if (Jim_PackageProvide(interp, "eventloop", "1.0", JIM_ERRMSG))
        return JIM_ERR;

    eventLoop = Jim_Alloc(sizeof(*eventLoop));
    eventLoop->fileEventHead = NULL;
    eventLoop->timeEventHead = NULL;
    eventLoop->timeEventNextId = 1;
    eventLoop->suppress_bgerror = 0;
    Jim_SetAssocData(interp, "eventloop", JimELAssocDataDeleProc, eventLoop);

    Jim_CreateCommand(interp, "vwait", JimELVwaitCommand, eventLoop, NULL);
    Jim_CreateCommand(interp, "update", JimELUpdateCommand, eventLoop, NULL);
    Jim_CreateCommand(interp, "after", JimELAfterCommand, eventLoop, NULL);

    return JIM_OK;
}
